#include "rclcpp/rclcpp.hpp"
#include "serial_driver/serial_driver.hpp"
#include <functional>
#include <geometry_msgs/msg/detail/twist__struct.hpp>
#include <limits>
#include <rclcpp/publisher.hpp>
#include <rclcpp/subscription.hpp>
#include <rclcpp/timer.hpp>
#include "nav_msgs/msg/odometry.hpp"
#include <tf2_ros/static_transform_broadcaster.h>
#include <tf2_ros/transform_broadcaster.h>

using namespace std::chrono_literals;

class Chat_STM32: public rclcpp::Node
{
  public:
    Chat_STM32():Node("chat_stm32_node_cpp")
    {
      pub_cmdvel_ = this->create_publisher<geometry_msgs::msg::Twist>("robot/speed", 10);
      // pub_robot_ = this->create_publisher<nav_msgs::msg::Odometry>("robot/speed", 10);
      //接受导航最后输出的速度
      sub_cmdvel_ = this->create_subscription<geometry_msgs::msg::Twist>("cmd_vel",10,std::bind(&Chat_STM32::cmdvel_callback,this,std::placeholders::_1));
      const std::string device_name = "/dev/mystm32";
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

        device_check_timer_ = this->create_wall_timer(
        5ms, std::bind(&Chat_STM32::send_timer, this));
        receive_stm32();

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
    std::memcpy(&send_buf[4], &robot_vx, 4);
    std::memcpy(&send_buf[8], &robot_vy, 4);
    std::memcpy(&send_buf[12], &nav_omega, 4);
    uint8_t crc=0;
    // crc = CRC16_Check(send_buf,12);
    send_buf[13]=crc>>8;
    send_buf[14]=crc;
    send_buf[15]=0xFF;

    std::vector<uint8_t> send_data(send_buf, send_buf + 16);
    try{
        // serial_driver_->port()->send(send_data);
        // RCLCPP_INFO(this->get_logger(),"发送数据： roll:%.2f , pitch:%.2f , yaw:%.2f",
        //     roll,pitch,yaw);
        std::ostringstream oss;
        oss << std::hex << std::setfill('0');   // 设置十六进制和补零

        for (size_t i = 0; i < 16; i++) {
            oss << "0x" << std::setw(2) << static_cast<int>(send_data[i]) << " ";
        }
        // RCLCPP_INFO(this->get_logger(), "%s", oss.str().c_str());
        } catch (const std::exception &ex)
        {
          RCLCPP_ERROR(this->get_logger(), "Failed to send data: %s", ex.what());
          return;
        }
  }

  void receive_stm32(){
    auto port = serial_driver_->port();
    port->async_receive([this](const std::vector<uint8_t> &data,const size_t &size) 
    {
        //打印16进制数据
        // std::ostringstream oss;
        // oss << std::hex << std::setfill('0');   // 设置十六进制和补零

        // for (size_t i = 0; i < size; i++) {
        //     oss << "0x" << std::setw(2) << static_cast<int>(data[i]) << " ";
        // }
        // RCLCPP_INFO(this->get_logger(), "Received data (%zu bytes): %s", size, oss.str().c_str());

        std::memcpy(&robot_vx,&data[0],4);
        std::memcpy(&robot_vy,&data[4],4);
        std::memcpy(&robot_omega, &data[8], 4);

        RCLCPP_INFO(this->get_logger(),
        "接收到的stm32数据是： robot_vx:%.2f , robot_vy:%.2f , robot_omega:%.2f",
                robot_vx,robot_vy,robot_omega);
      /*
        //发布底盘速度 供给ekf融合使用
        auto robot_msg = nav_msgs::msg::Odometry();
        robot_msg.header.stamp = this->now();
        robot_msg.header.frame_id = "odom";
        robot_msg.child_frame_id = "base_link";
        robot_msg.twist.twist.linear.x = robot_vx;
        robot_msg.twist.twist.linear.y = robot_vy;
        robot_msg.twist.twist.angular.z = robot_omega;
        // robot_msg.pose.pose.position.x = odom_x;
        // robot_msg.pose.pose.position.y = odom_y;
        // robot_msg.pose.pose.position.z = 0.0;
        pub_robot_->publish(robot_msg);
      */
        //发布底盘速度 供给计算odom使用
        auto cmdvel_msg = geometry_msgs::msg::Twist();
        cmdvel_msg.linear.x = robot_vx;
        cmdvel_msg.linear.y = robot_vy;
        cmdvel_msg.angular.z = robot_omega;
        pub_cmdvel_->publish(cmdvel_msg);
        // 继续监听新的数据
        receive_stm32();
    }
    );
  }

    std::shared_ptr<drivers::serial_driver::SerialDriver> serial_driver_;
    std::shared_ptr<drivers::common::IoContext> io_context_;
    rclcpp::TimerBase::SharedPtr device_check_timer_;
    rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr pub_robot_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr pub_cmdvel_;
    rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr sub_cmdvel_;
    float nav_x,nav_y,nav_omega;  
    

    // float roll,pitch,yaw;
    // float odom_x=0.0,odom_y=0.0;
    float robot_vx,robot_vy,robot_omega;
    // float dt = 0.05;
    

};

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);

  rclcpp::spin(std::make_shared<Chat_STM32>());

  rclcpp::shutdown();
  return 0;
}