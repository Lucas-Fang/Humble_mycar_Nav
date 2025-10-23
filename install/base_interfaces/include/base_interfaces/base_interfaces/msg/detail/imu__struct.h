// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from base_interfaces:msg/Imu.idl
// generated code does not contain a copyright notice

#ifndef BASE_INTERFACES__MSG__DETAIL__IMU__STRUCT_H_
#define BASE_INTERFACES__MSG__DETAIL__IMU__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Imu in the package base_interfaces.
typedef struct base_interfaces__msg__Imu
{
  float roll;
  float pitch;
  float yaw;
} base_interfaces__msg__Imu;

// Struct for a sequence of base_interfaces__msg__Imu.
typedef struct base_interfaces__msg__Imu__Sequence
{
  base_interfaces__msg__Imu * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} base_interfaces__msg__Imu__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // BASE_INTERFACES__MSG__DETAIL__IMU__STRUCT_H_
