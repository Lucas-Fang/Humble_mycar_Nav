#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg//imu.hpp"
#include <geometry_msgs/msg/detail/twist__struct.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <rclcpp/timer.hpp>
#include "nav_msgs/msg/odometry.hpp"
#include <tf2_ros/transform_broadcaster.h>

typedef struct
{
    float accx;
    float accy;
    float accz;
    float gyrox;
    float gyroy;
    float gyroz;
    double roll;
    double pitch;
    double yaw;
}IMU_Data;
struct Quaternion {
  float w;  // 实部（标量部分）
  float x;  // 虚部（i轴分量）
  float y;  // 虚部（j轴分量）
  float z;  // 虚部（k轴分量）
};

using namespace std::chrono_literals;

class Cala_Odom: public rclcpp::Node
{
  public:
    Cala_Odom():Node("cala_odom_node_cpp")
    {
        last_time_ = this->now();
        //订阅imu消息
        sub_imu_ = this->create_subscription<sensor_msgs::msg::Imu>("imu/data", 10, 
          std::bind(&Cala_Odom::imu_callback, this, std::placeholders::_1));
        //订阅机器人速度消息
        sub_robot_ = this->create_subscription<geometry_msgs::msg::Twist>("robot/speed", 10, 
          std::bind(&Cala_Odom::topic_callback, this, std::placeholders::_1));
        // 创建里程计发布者
        pub_odom_ = this->create_publisher<nav_msgs::msg::Odometry>("odom", 10);
        // 创建定时器计算里程计并发布
        timer_ = this->create_wall_timer(
            10ms, std::bind(&Cala_Odom::timer_callback, this));

        //发布odom到base_link的tf变换
        //创建动态变换发布者
        odom_tf_pub_ = std::make_shared<tf2_ros::TransformBroadcaster>(this);
          
    }
    private:
      void imu_callback(const sensor_msgs::msg::Imu::ConstSharedPtr msg)
      {
        tf2::Quaternion q(  
            msg->orientation.x,
            msg->orientation.y,
            msg->orientation.z,
            msg->orientation.w);
        q.normalize();
        q_x=msg->orientation.x;
        q_y=msg->orientation.y;
        q_z=msg->orientation.z;
        q_w=msg->orientation.w;
        //   四元数转换为欧拉角
        tf2::Matrix3x3 m(q);
        //   转换为角度制
        m.getRPY(imu_data.roll, imu_data.pitch, imu_data.yaw);
        imu_data.accx = msg->linear_acceleration.x;
        imu_data.accy = msg->linear_acceleration.y;
        imu_data.accz = msg->linear_acceleration.z;
        imu_data.gyrox = msg->angular_velocity.x;
        imu_data.gyroy = msg->angular_velocity.y;
        imu_data.gyroz = msg->angular_velocity.z;

        // RCLCPP_INFO(this->get_logger(),
        // "订阅到的四元数消息是： x:%.2f , y:%.2f , z:%.2f , w:%.2f",
        //     msg->orientation.x,msg->orientation.y,msg->orientation.z,msg->orientation.w);
      }
      void topic_callback(const geometry_msgs::msg::Twist::ConstSharedPtr msg)
      {
          // RCLCPP_INFO(this->get_logger(),"订阅到的机器人速度消息是： robot_vx:%.2f , robot_vy:%.2f ",
          //     msg->v_x,msg->v_y);
          robot_vx=msg->linear.x;
          robot_vy=msg->linear.y;
      }
      // 定时器回调函数
      void timer_callback()
      {   auto timestamp = this->now();  // 统一时间戳
          Get_Odometry();
          // 发布里程计消息
          auto odom_msg = nav_msgs::msg::Odometry();
          odom_msg.header.stamp = timestamp;
          odom_msg.header.frame_id = "odom";
          odom_msg.child_frame_id = "base_link";
          odom_msg.pose.pose.position.x = odom_x;
          odom_msg.pose.pose.position.y = odom_y;
          odom_msg.pose.pose.position.z = 0.0;
          // 四元数表示姿态
        //   tf2::Quaternion q;
        //   q.setRPY(deg2Rad(roll), deg2Rad(pitch), deg2Rad(yaw));
          odom_msg.pose.pose.orientation.x = q_x;
          odom_msg.pose.pose.orientation.y = q_y;
          odom_msg.pose.pose.orientation.z = q_z;
          odom_msg.pose.pose.orientation.w = q_w;
          // 线速度
          odom_msg.twist.twist.linear.x = robot_vx;
          odom_msg.twist.twist.linear.y = robot_vy;
          odom_msg.twist.twist.linear.z = 0.0;
          // 角速度
          odom_msg.twist.twist.angular.x = 0;
          odom_msg.twist.twist.angular.y = 0;
          odom_msg.twist.twist.angular.z = imu_data.gyroz; 
          pub_odom_->publish(odom_msg);


          // this->pub_transforms();
          geometry_msgs::msg::TransformStamped odom_tf;
          odom_tf.header.stamp = timestamp ;
          odom_tf.header.frame_id = "odom";
          odom_tf.child_frame_id = "base_link";
          odom_tf.transform.translation.x = odom_x;
          odom_tf.transform.translation.y = odom_y;
          odom_tf.transform.translation.z = 0.0;
          // tf2::Quaternion q;
          // q.setRPY(0, 0, imu_data.yaw);
          odom_tf.transform.rotation.x = q_x;
          odom_tf.transform.rotation.y = q_y;
          odom_tf.transform.rotation.z = q_z;
          odom_tf.transform.rotation.w = q_w;
          odom_tf_pub_->sendTransform(odom_tf);


          RCLCPP_INFO(this->get_logger(),"发布的里程计消息是： odom_x:%.2f , odom_y:%.2f  , yaw:%.2f",
              odom_msg.pose.pose.position.x,odom_msg.pose.pose.position.y,imu_data.yaw*(180.0/M_PI));
      }

      void pub_transforms(){

      }

      void Get_Odometry(){
        auto now = this->now();
        float dt = (now - last_time_).seconds();
        last_time_ = now;
        
        World_vx = robot_vx * cos(imu_data.yaw) - robot_vy * sin(imu_data.yaw);
        World_vy = robot_vx * sin(imu_data.yaw) + robot_vy * cos(imu_data.yaw);
        odom_x += World_vx * dt;
        odom_y += World_vy * dt;

    }
    float deg2Rad(double degrees) {
        return degrees * (M_PI / 180.0);
    }

      rclcpp::Subscription<sensor_msgs::msg::Imu>::SharedPtr sub_imu_;
      rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr sub_robot_;
      rclcpp::TimerBase::SharedPtr timer_;
      rclcpp::Publisher<nav_msgs::msg::Odometry>::SharedPtr pub_odom_;
      std::shared_ptr<tf2_ros::TransformBroadcaster> odom_tf_pub_;
rclcpp::Time last_time_;
      double q_x=0,q_y=0,q_z=0,q_w=0;
      // double roll,pitch,yaw;
      IMU_Data imu_data;
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

