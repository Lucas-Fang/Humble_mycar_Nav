// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from base_interfaces:msg/Imu.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__MSG__DETAIL__IMU__BUILDER_HPP_
#define BASE_INTERFACES__MSG__DETAIL__IMU__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "base_interfaces/msg/detail/imu__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace base_interfaces
{

namespace msg
{

namespace builder
{

class Init_Imu_yaw
{
public:
  explicit Init_Imu_yaw(::base_interfaces::msg::Imu & msg)
  : msg_(msg)
  {}
  ::base_interfaces::msg::Imu yaw(::base_interfaces::msg::Imu::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return std::move(msg_);
  }

private:
  ::base_interfaces::msg::Imu msg_;
};

class Init_Imu_pitch
{
public:
  explicit Init_Imu_pitch(::base_interfaces::msg::Imu & msg)
  : msg_(msg)
  {}
  Init_Imu_yaw pitch(::base_interfaces::msg::Imu::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_Imu_yaw(msg_);
  }

private:
  ::base_interfaces::msg::Imu msg_;
};

class Init_Imu_roll
{
public:
  Init_Imu_roll()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Imu_pitch roll(::base_interfaces::msg::Imu::_roll_type arg)
  {
    msg_.roll = std::move(arg);
    return Init_Imu_pitch(msg_);
  }

private:
  ::base_interfaces::msg::Imu msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::base_interfaces::msg::Imu>()
{
  return base_interfaces::msg::builder::Init_Imu_roll();
}

}  // namespace base_interfaces

#endif  // BASE_INTERFACES__MSG__DETAIL__IMU__BUILDER_HPP_
