#include "rclcpp/rclcpp.hpp"
#include "serial_driver/serial_driver.hpp"
#include <base_interfaces/msg/detail/imu__struct.hpp>
#include <filesystem>
#include <memory>
#include "serial_pkg/crc16.h"
#include "sensor_msgs/msg//imu.hpp"
#include "geometry_msgs/msg/quaternion.hpp"
#include <tf2/LinearMath/Quaternion.h>
#include "base_interfaces/msg/imu.hpp"


using namespace std::chrono_literals;

struct IMUData {
    float roll;
    float pitch;
    float yaw;
};

class Serial_Node : public rclcpp::Node
{
public:
  Serial_Node() : Node("serial_node_cpp")
  {
    //设置发布方
    imu_pub_ = this->create_publisher<sensor_msgs::msg::Imu>("imu/data", 10);
    // 等设备准备好再初始化
    my_imu_pub_ = this->create_publisher<base_interfaces::msg::Imu>("myimu/data", 10);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    // 串口设备名（根据实际设备调整）
    const std::string device_name = "/dev/dm_imu";

    RCLCPP_INFO(this->get_logger(), "Serial port Node Open!");
    // 创建串口配置对象
    // 波特率115200；不开启流控制；无奇偶效验；停止位1。
    drivers::serial_driver::SerialPortConfig config(
        921600,
        drivers::serial_driver::FlowControl::NONE,
        drivers::serial_driver::Parity::NONE,
        drivers::serial_driver::StopBits::ONE);
    
    // 初始化串口
    try
    {
      io_context_ = std::make_shared<drivers::common::IoContext>(1);
      // 初始化 serial_driver_
      serial_driver_ = std::make_shared<drivers::serial_driver::SerialDriver>(*io_context_);
      serial_driver_->init_port(device_name, config);
      serial_driver_->port()->open();
      
      RCLCPP_INFO(this->get_logger(), "Serial port initialized successfully");
      RCLCPP_INFO(this->get_logger(), "Using device: %s", serial_driver_->port().get()->device_name().c_str());
      RCLCPP_INFO(this->get_logger(), "Baud_rate: %d", config.get_baud_rate());
    }
    catch (const std::exception &ex)
    {
      RCLCPP_ERROR(this->get_logger(), "Failed to initialize serial port: %s", ex.what());
      return;
    }

    async_receive_message();

  // imu_pub_ = this->create_publisher<sensor_msgs::msg::Imu>("imu/data", 10);

  // // 初始化时不连接，等待定时器检查设备
  // serial_driver_.reset();
  // // 周期性检查 /dev/ttyACM* 是否存在
  // device_check_timer_ = this->create_wall_timer(
  //   500ms, std::bind(&Serial_Node::check_and_connect, this));
  }

private:
  void check_and_connect()
  {
    // 如果已经连接成功，就不再检查
    if (serial_driver_ && serial_driver_->port()->is_open()) {
      return;
    }

    // 扫描 /dev/ttyACM* 设备
    std::string found_device;
    for (const auto & entry : std::filesystem::directory_iterator("/dev")) {
      std::string name = entry.path().string();
      if (name.find("ttyACM") != std::string::npos) {
        found_device = name;
        break;
      }
    }

    if (found_device.empty()) {
      RCLCPP_WARN(this->get_logger(), "No /dev/ttyACM* device found, retrying...");
      return;
    }

    RCLCPP_INFO(this->get_logger(), "Found device: %s", found_device.c_str());

    // 初始化串口
    try {
      drivers::serial_driver::SerialPortConfig config(
        921600,
        drivers::serial_driver::FlowControl::NONE,
        drivers::serial_driver::Parity::NONE,
        drivers::serial_driver::StopBits::ONE);

      io_context_ = std::make_shared<drivers::common::IoContext>(1);
      serial_driver_ = std::make_shared<drivers::serial_driver::SerialDriver>(*io_context_);
      serial_driver_->init_port(found_device, config);
      serial_driver_->port()->open();

      RCLCPP_INFO(this->get_logger(), "Serial port opened on %s", found_device.c_str());

      // 延迟发送 IMU 重启命令
      // restart_timer_ = this->create_wall_timer(
      //   200ms, std::bind(&Serial_Node::send_imu_restart, this));

      // 启动异步接收
      async_receive_message();

    } catch (const std::exception & ex) {
      RCLCPP_ERROR(this->get_logger(), "Failed to open serial port: %s", ex.what());
      serial_driver_.reset();
    }
  }
  //imu重启命令
  void send_imu_restart()
  {
    if (!serial_driver_ || !serial_driver_->port()->is_open()) return;

    std::vector<uint8_t> restart_cmd = {0xAA, 0x00, 0x00, 0x0D};
    try {
      serial_driver_->port()->send(restart_cmd);
      RCLCPP_INFO(this->get_logger(), "Sent IMU restart command");
    } catch (const std::exception & ex) {
      RCLCPP_ERROR(this->get_logger(), "Failed to send restart cmd: %s", ex.what());
    }

    // 只发一次就取消定时器
    restart_timer_->cancel();
  }

  //接收函数
  void async_receive_message()  //创建一个函数更方便重新调用
  {
    //注册回调函数
    auto port = serial_driver_->port();
    // 设置接收回调函数
    port->async_receive([this](const std::vector<uint8_t> &data,const size_t &size) 
    {
        recv_buffer_.insert(recv_buffer_.end(), data.begin(), data.begin() + size);
        parse_buffer();

        // 继续监听新的数据
        async_receive_message();
    }
    );
  }
  void parse_buffer()
  {
    while (recv_buffer_.size() >= 19) { // 至少一帧
        // 找帧头
        if (recv_buffer_[0] != 0x55 || recv_buffer_[1] != 0xAA) {
            recv_buffer_.erase(recv_buffer_.begin());
            continue;
        }

        // 取一帧
        std::vector<uint8_t> frame(recv_buffer_.begin(), recv_buffer_.begin() + 19);

        // 校验 CRC16
        uint16_t crc_in_frame = (uint16_t)frame[16] | ((uint16_t)frame[17] << 8);
        uint16_t crc_calc = Get_CRC16(frame.data(), 16);
        IMUData imu{};
        if (crc_in_frame == crc_calc) {
            // 只处理 index=0x03 的帧
            if (frame[3] == 0x03) {
                
                std::memcpy(&imu.roll,  &frame[4], 4);
                std::memcpy(&imu.pitch, &frame[8], 4);
                std::memcpy(&imu.yaw,   &frame[12],4);

                // tf2::Quaternion q;
                // q.setRPY(imu.roll, imu.pitch, imu.yaw);
                // sensor_msgs::msg::Imu imu_msg;

                // imu_msg.header.stamp = this->now();
                // imu_msg.header.frame_id = "imu_link";
                // imu_msg.orientation.x = q.x();
                // imu_msg.orientation.y = q.y();
                // imu_msg.orientation.z = q.z();
                // imu_msg.orientation.w = q.w();
                // imu_pub_->publish(imu_msg);
                // 发布自定义 IMU 消息
                base_interfaces::msg::Imu my_imu_msg;
                my_imu_msg.pitch = imu.pitch;
                my_imu_msg.roll = imu.roll;
                my_imu_msg.yaw = imu.yaw;
                my_imu_pub_->publish(my_imu_msg);
                
                // RCLCPP_INFO(this->get_logger(),
                //     "IMU RPY: roll=%.2f, pitch=%.2f, yaw=%.2f",
                //     imu.roll, imu.pitch, imu.yaw);
                
            }
        } else {
            // RCLCPP_WARN(this->get_logger(), "CRC mismatch, drop frame");
        }

        // 删除已处理帧
        recv_buffer_.erase(recv_buffer_.begin(), recv_buffer_.begin() + 19);

    }
    }

  std::shared_ptr<drivers::serial_driver::SerialDriver> serial_driver_;
  std::shared_ptr<drivers::common::IoContext> io_context_;
  // std::vector<uint8_t> receive_data_buffer = std::vector<uint8_t>(1024); // 接收缓冲区
  std::vector<uint8_t> recv_buffer_;
  rclcpp::TimerBase::SharedPtr device_check_timer_;
  rclcpp::TimerBase::SharedPtr restart_timer_;

  rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_pub_;
  rclcpp::Publisher<base_interfaces::msg::Imu>::SharedPtr my_imu_pub_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);
  auto node = std::make_shared<Serial_Node>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}

