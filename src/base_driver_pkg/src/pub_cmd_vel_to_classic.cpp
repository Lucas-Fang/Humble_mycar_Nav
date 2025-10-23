#include "rclcpp/rclcpp.hpp"
#include "serial_driver/serial_driver.hpp"
// #include <functional>
#include <geometry_msgs/msg/detail/twist__struct.hpp>
// #include <limits>
#include <rclcpp/subscription.hpp>
#include <rclcpp/timer.hpp>

using namespace std::chrono_literals;

class Send_STM32: public rclcpp::Node
{
  public:
    Send_STM32():Node("pub_cmd_vel_to_classic")
    {
      // pub_robot_ = this->create_publisher<nav_msgs::msg::Odometry>("robot/speed", 10);
      //接受导航最后输出的速度
      sub_cmdvel_ = this->create_subscription<geometry_msgs::msg::Twist>("cmd_vel",10,std::bind(&Send_STM32::cmdvel_callback,this,std::placeholders::_1));
      
      const std::string device_name = "/dev/ttyUSB0";
      RCLCPP_INFO(this->get_logger(), "Serial port Node Open!");

      // 创建串口配置对象
      drivers::serial_driver::SerialPortConfig config(
          115200,
          drivers::serial_driver::FlowControl::NONE,
          drivers::serial_driver::Parity::NONE,
          drivers::serial_driver::StopBits::ONE);
        // 初始化串口
        try
        {
          io_context_ = std::make_shared<drivers::common::IoContext>(1);
          // 初始化 serial_driver_ 初始化串口
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

        timer_ = this->create_wall_timer(
        5ms, std::bind(&Send_STM32::send_timer, this));

    }
  private:

  void cmdvel_callback(const geometry_msgs::msg::Twist::SharedPtr msg){
    nav_x = msg->linear.x;
    nav_y = msg->linear.y;
    nav_omega = msg->angular.z;
    // RCLCPP_INFO(this->get_logger(),"接收到的cmd_vel数据是： nav_x:%.2f , nav_y:%.2f , nav_omega:%.2f",
  }

  void send_timer(){
    if (!serial_driver_ || !serial_driver_->port()->is_open()) return;
    uint8_t send_buf[16];
    send_buf[0]=0xA5;//帧头
    send_buf[1]=0x5A;
    send_buf[2]=12; //长度
    send_buf[3]=0;  //CMD
    nav_x = 1.21;
    nav_y = 2.13;
    std::memcpy(&send_buf[4], &nav_x, 4);
    std::memcpy(&send_buf[8], &nav_y, 4);
    std::memcpy(&send_buf[12], &nav_omega, 4);
    uint8_t crc=0;
    crc = CRC16_Check(send_buf,12);
    send_buf[13]=crc>>8;
    send_buf[14]=crc;
    send_buf[15]=0xFF;

    std::vector<uint8_t> send_data(send_buf, send_buf + 16);
    try{
        serial_driver_->port()->send(send_data);
        // // RCLCPP_INFO(this->get_logger(),"发送数据： roll:%.2f , pitch:%.2f , yaw:%.2f",
        // //     roll,pitch,yaw);
        // std::ostringstream oss;
        // oss << std::hex << std::setfill('0');   // 设置十六进制和补零

        // for (size_t i = 0; i < 16; i++) {
        //     oss << "0x" << std::setw(2) << static_cast<int>(send_data[i]) << " ";
        // }
        // RCLCPP_INFO(this->get_logger(), "%s", oss.str().c_str());
        } catch (const std::exception &ex)
        {
          RCLCPP_ERROR(this->get_logger(), "Failed to send data: %s", ex.what());
          return;
        }
    
  }
    uint16_t CRC16_Check(const uint8_t *data, uint8_t len)
    {
        uint16_t CRC16 = 0xFFFF;
        uint8_t state, i, j;
        for (i = 0; i < len; i++)
        {
            CRC16 ^= data[i];
            for (j = 0; j < 8; j++)
            {
                state = CRC16 & 0x01;
                CRC16 >>= 1;
                if (state)
                {
                    CRC16 ^= 0xA001;
                }
            }
        }
        return CRC16;
    }

    std::shared_ptr<drivers::serial_driver::SerialDriver> serial_driver_;
    std::shared_ptr<drivers::common::IoContext> io_context_;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr sub_cmdvel_;
    rclcpp::TimerBase::SharedPtr timer_;
    float nav_x,nav_y,nav_omega;  
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);

  rclcpp::spin(std::make_shared<Send_STM32>());

  rclcpp::shutdown();
  return 0;
}