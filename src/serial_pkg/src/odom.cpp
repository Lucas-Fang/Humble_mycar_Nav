#include "rclcpp/rclcpp.hpp"
// #include "sensor_msgs/msg//imu.hpp"
#include <tf2/LinearMath/Quaternion.h>
// #include <tf2/LinearMath/Matrix3x3.h>
#include "base_interfaces/msg/imu.hpp"
#include "base_interfaces/msg/robot.hpp"
#include <rclcpp/timer.hpp>
#include "nav_msgs/msg/odometry.hpp"
#include <tf2_ros/static_transform_broadcaster.h>

using namespace std::chrono_literals;

class Cala_Odom: public rclcpp::Node
{
  public:
    Cala_Odom():Node("cala_odom_node_cpp")
    {
        //订阅自己定义的imu消息
        sub_my_imu_ = this->create_subscription<base_interfaces::msg::Imu>("myimu/data", 10, 
          std::bind(&Cala_Odom::imu_callback, this, std::placeholders::_1));
        //订阅机器人速度消息
        sub_my_robot_ = this->create_subscription<base_interfaces::msg::Robot>("robot/speed", 10, 
          std::bind(&Cala_Odom::topic_callback, this, std::placeholders::_1));
        // 创建里程计发布者
        pub_odom_ = this->create_publisher<nav_msgs::msg::Odometry>("odom/data", 10);
        // 创建定时器计算里程计并发布
        timer_ = this->create_wall_timer(
            10ms, std::bind(&Cala_Odom::timer_callback, this));

        //发布odom到base_link的tf变换
        //创建静态变换发布者
          odom_tf_pub_ = std::make_shared<tf2_ros::StaticTransformBroadcaster>(this);
          
    }
    private:
      void imu_callback(const base_interfaces::msg::Imu::ConstSharedPtr msg)
      {
          // RCLCPP_INFO(this->get_logger(),"订阅到的IMU消息是： roll:%.2f , pitch:%.2f , yaw:%.2f",
          //     msg->roll,msg->pitch,msg->yaw);
          roll=msg->roll;
          pitch=msg->pitch;
          yaw=msg->yaw;
      }
      void topic_callback(const base_interfaces::msg::Robot::ConstSharedPtr msg)
      {
          // RCLCPP_INFO(this->get_logger(),"订阅到的机器人速度消息是： robot_vx:%.2f , robot_vy:%.2f ",
          //     msg->v_x,msg->v_y);
          robot_vx=msg->v_x;
          robot_vy=msg->v_y;
      }
      // 定时器回调函数
      void timer_callback()
      {
          Get_Odometry();
          // RCLCPP_INFO(this->get_logger(),"计算得到的里程计是： odom_x:%.2f , odom_y:%.2f  , yaw:%.2f",
          //     odom_x,odom_y,yaw);
          // 发布里程计消息
          auto odom_msg = nav_msgs::msg::Odometry();
          odom_msg.header.stamp = this->now();
          odom_msg.header.frame_id = "odom";
          odom_msg.child_frame_id = "base_link";
          odom_msg.pose.pose.position.x = odom_x;
          odom_msg.pose.pose.position.y = odom_y;
          odom_msg.pose.pose.position.z = 0.0;
          // 四元数表示姿态
          tf2::Quaternion q;
          q.setRPY(deg2Rad(roll), deg2Rad(pitch), deg2Rad(yaw));
          odom_msg.pose.pose.orientation.x = q.x();
          odom_msg.pose.pose.orientation.y = q.y();
          odom_msg.pose.pose.orientation.z = q.z();
          odom_msg.pose.pose.orientation.w = q.w();
          // 线速度
          odom_msg.twist.twist.linear.x = robot_vx;
          odom_msg.twist.twist.linear.y = robot_vy;
          odom_msg.twist.twist.linear.z = 0.0;
          // 角速度
          odom_msg.twist.twist.angular.x = 0.0;
          odom_msg.twist.twist.angular.y = 0.0;
          odom_msg.twist.twist.angular.z = 0.0; // 假设没有角速度信息
          pub_odom_->publish(odom_msg);
          this->pub_transforms();
          RCLCPP_INFO(this->get_logger(),"发布的里程计消息是： odom_x:%.2f , odom_y:%.2f  , yaw:%.2f",
              odom_msg.pose.pose.position.x,odom_msg.pose.pose.position.y,yaw);
      }

      void pub_transforms(){
          geometry_msgs::msg::TransformStamped odom_tf;
          odom_tf.header.stamp = this->now();
          odom_tf.header.frame_id = "odom";
          odom_tf.child_frame_id = "base_link";
          odom_tf.transform.translation.x = odom_x;
          odom_tf.transform.translation.y = odom_y;
          odom_tf.transform.translation.z = 0.0;
          tf2::Quaternion q;
          q.setRPY(0, 0, deg2Rad(yaw));
          odom_tf.transform.rotation.x = q.x();
          odom_tf.transform.rotation.y = q.y();
          odom_tf.transform.rotation.z = q.z();
          odom_tf.transform.rotation.w = q.w();
          odom_tf_pub_->sendTransform(odom_tf);
      }

      void Get_Odometry(){
        float dt = 0.01;//s 10ms

        World_vx = robot_vx * cos(deg2Rad(yaw)) - robot_vy * sin(deg2Rad(yaw));
        World_vy = robot_vx * sin(deg2Rad(yaw)) + robot_vy * cos(deg2Rad(yaw));

        odom_x += World_vx * dt;
        odom_y += World_vy * dt;

    }
    float deg2Rad(double degrees) {
        return degrees * (3.1415927 / 180.0);
    }


      rclcpp::Subscription<base_interfaces::msg::Imu>::SharedPtr sub_my_imu_;
      rclcpp::Subscription<base_interfaces::msg::Robot>::SharedPtr sub_my_robot_;
      rclcpp::TimerBase::SharedPtr timer_;
      rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr pub_odom_;
      std::shared_ptr<tf2_ros::StaticTransformBroadcaster> odom_tf_pub_;
      float roll,pitch,yaw;
      float robot_vx,robot_vy,World_vx,World_vy;
      float odom_x=0.0,odom_y=0.0;


};

int main(int argc, char ** argv)
{
  rclcpp::init(argc,argv);

  rclcpp::spin(std::make_shared<Cala_Odom>());

  rclcpp::shutdown();
  return 0;
}