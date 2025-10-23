// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from base_interfaces:msg/Robot.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__MSG__DETAIL__ROBOT__BUILDER_HPP_
#define BASE_INTERFACES__MSG__DETAIL__ROBOT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "base_interfaces/msg/detail/robot__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace base_interfaces
{

namespace msg
{

namespace builder
{

class Init_Robot_v_omega
{
public:
  explicit Init_Robot_v_omega(::base_interfaces::msg::Robot & msg)
  : msg_(msg)
  {}
  ::base_interfaces::msg::Robot v_omega(::base_interfaces::msg::Robot::_v_omega_type arg)
  {
    msg_.v_omega = std::move(arg);
    return std::move(msg_);
  }

private:
  ::base_interfaces::msg::Robot msg_;
};

class Init_Robot_v_y
{
public:
  explicit Init_Robot_v_y(::base_interfaces::msg::Robot & msg)
  : msg_(msg)
  {}
  Init_Robot_v_omega v_y(::base_interfaces::msg::Robot::_v_y_type arg)
  {
    msg_.v_y = std::move(arg);
    return Init_Robot_v_omega(msg_);
  }

private:
  ::base_interfaces::msg::Robot msg_;
};

class Init_Robot_v_x
{
public:
  Init_Robot_v_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Robot_v_y v_x(::base_interfaces::msg::Robot::_v_x_type arg)
  {
    msg_.v_x = std::move(arg);
    return Init_Robot_v_y(msg_);
  }

private:
  ::base_interfaces::msg::Robot msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::base_interfaces::msg::Robot>()
{
  return base_interfaces::msg::builder::Init_Robot_v_x();
}

}  // namespace base_interfaces

#endif  // BASE_INTERFACES__MSG__DETAIL__ROBOT__BUILDER_HPP_
