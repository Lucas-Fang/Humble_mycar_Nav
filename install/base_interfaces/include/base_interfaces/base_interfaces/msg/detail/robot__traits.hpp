// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from base_interfaces:msg/Robot.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__MSG__DETAIL__ROBOT__TRAITS_HPP_
#define BASE_INTERFACES__MSG__DETAIL__ROBOT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "base_interfaces/msg/detail/robot__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace base_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const Robot & msg,
  std::ostream & out)
{
  out << "{";
  // member: v_x
  {
    out << "v_x: ";
    rosidl_generator_traits::value_to_yaml(msg.v_x, out);
    out << ", ";
  }

  // member: v_y
  {
    out << "v_y: ";
    rosidl_generator_traits::value_to_yaml(msg.v_y, out);
    out << ", ";
  }

  // member: v_omega
  {
    out << "v_omega: ";
    rosidl_generator_traits::value_to_yaml(msg.v_omega, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Robot & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: v_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "v_x: ";
    rosidl_generator_traits::value_to_yaml(msg.v_x, out);
    out << "\n";
  }

  // member: v_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "v_y: ";
    rosidl_generator_traits::value_to_yaml(msg.v_y, out);
    out << "\n";
  }

  // member: v_omega
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "v_omega: ";
    rosidl_generator_traits::value_to_yaml(msg.v_omega, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Robot & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace base_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use base_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const base_interfaces::msg::Robot & msg,
  std::ostream & out, size_t indentation = 0)
{
  base_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use base_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const base_interfaces::msg::Robot & msg)
{
  return base_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<base_interfaces::msg::Robot>()
{
  return "base_interfaces::msg::Robot";
}

template<>
inline const char * name<base_interfaces::msg::Robot>()
{
  return "base_interfaces/msg/Robot";
}

template<>
struct has_fixed_size<base_interfaces::msg::Robot>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<base_interfaces::msg::Robot>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<base_interfaces::msg::Robot>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // BASE_INTERFACES__MSG__DETAIL__ROBOT__TRAITS_HPP_
