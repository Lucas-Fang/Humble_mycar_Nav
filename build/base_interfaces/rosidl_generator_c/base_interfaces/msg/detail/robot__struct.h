// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from base_interfaces:msg/Robot.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__MSG__DETAIL__ROBOT__STRUCT_H_
#define BASE_INTERFACES__MSG__DETAIL__ROBOT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Robot in the package base_interfaces.
typedef struct base_interfaces__msg__Robot
{
  float v_x;
  float v_y;
  float v_omega;
} base_interfaces__msg__Robot;

// Struct for a sequence of base_interfaces__msg__Robot.
typedef struct base_interfaces__msg__Robot__Sequence
{
  base_interfaces__msg__Robot * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces__msg__Robot__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BASE_INTERFACES__MSG__DETAIL__ROBOT__STRUCT_H_
