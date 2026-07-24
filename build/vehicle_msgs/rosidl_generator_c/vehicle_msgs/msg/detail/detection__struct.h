// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_msgs:msg/Detection.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_MSGS__MSG__DETAIL__DETECTION__STRUCT_H_
#define VEHICLE_MSGS__MSG__DETAIL__DETECTION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'label'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/Detection in the package vehicle_msgs.
typedef struct vehicle_msgs__msg__Detection
{
  rosidl_runtime_c__String label;
  float confidence;
  float x_min;
  float y_min;
  float x_max;
  float y_max;
} vehicle_msgs__msg__Detection;

// Struct for a sequence of vehicle_msgs__msg__Detection.
typedef struct vehicle_msgs__msg__Detection__Sequence
{
  vehicle_msgs__msg__Detection * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_msgs__msg__Detection__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_MSGS__MSG__DETAIL__DETECTION__STRUCT_H_
