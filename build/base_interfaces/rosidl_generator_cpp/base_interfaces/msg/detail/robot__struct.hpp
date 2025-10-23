// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from base_interfaces:msg/Robot.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__MSG__DETAIL__ROBOT__STRUCT_HPP_
#define BASE_INTERFACES__MSG__DETAIL__ROBOT__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__base_interfaces__msg__Robot __attribute__((deprecated))
#else
# define DEPRECATED__base_interfaces__msg__Robot __declspec(deprecated)
#endif

namespace base_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Robot_
{
  using Type = Robot_<ContainerAllocator>;

  explicit Robot_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->v_x = 0.0f;
      this->v_y = 0.0f;
      this->v_omega = 0.0f;
    }
  }

  explicit Robot_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->v_x = 0.0f;
      this->v_y = 0.0f;
      this->v_omega = 0.0f;
    }
  }

  // field types and members
  using _v_x_type =
    float;
  _v_x_type v_x;
  using _v_y_type =
    float;
  _v_y_type v_y;
  using _v_omega_type =
    float;
  _v_omega_type v_omega;

  // setters for named parameter idiom
  Type & set__v_x(
    const float & _arg)
  {
    this->v_x = _arg;
    return *this;
  }
  Type & set__v_y(
    const float & _arg)
  {
    this->v_y = _arg;
    return *this;
  }
  Type & set__v_omega(
    const float & _arg)
  {
    this->v_omega = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    base_interfaces::msg::Robot_<ContainerAllocator> *;
  using ConstRawPtr =
    const base_interfaces::msg::Robot_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<base_interfaces::msg::Robot_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<base_interfaces::msg::Robot_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      base_interfaces::msg::Robot_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<base_interfaces::msg::Robot_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      base_interfaces::msg::Robot_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<base_interfaces::msg::Robot_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<base_interfaces::msg::Robot_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<base_interfaces::msg::Robot_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__base_interfaces__msg__Robot
    std::shared_ptr<base_interfaces::msg::Robot_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__base_interfaces__msg__Robot
    std::shared_ptr<base_interfaces::msg::Robot_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Robot_ & other) const
  {
    if (this->v_x != other.v_x) {
      return false;
    }
    if (this->v_y != other.v_y) {
      return false;
    }
    if (this->v_omega != other.v_omega) {
      return false;
    }
    return true;
  }
  bool operator!=(const Robot_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Robot_

// alias to use template instance with default allocator
using Robot =
  base_interfaces::msg::Robot_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace base_interfaces

#endif  // BASE_INTERFACES__MSG__DETAIL__ROBOT__STRUCT_HPP_
