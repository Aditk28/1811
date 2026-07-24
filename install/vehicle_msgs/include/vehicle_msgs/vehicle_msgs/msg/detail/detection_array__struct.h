// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from vehicle_msgs:msg/DetectionArray.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_MSGS__MSG__DETAIL__DETECTION_ARRAY__STRUCT_H_
#define VEHICLE_MSGS__MSG__DETAIL__DETECTION_ARRAY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'detections'
#include "vehicle_msgs/msg/detail/detection__struct.h"

/// Struct defined in msg/DetectionArray in the package vehicle_msgs.
typedef struct vehicle_msgs__msg__DetectionArray
{
  std_msgs__msg__Header header;
  vehicle_msgs__msg__Detection__Sequence detections;
} vehicle_msgs__msg__DetectionArray;

// Struct for a sequence of vehicle_msgs__msg__DetectionArray.
typedef struct vehicle_msgs__msg__DetectionArray__Sequence
{
  vehicle_msgs__msg__DetectionArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} vehicle_msgs__msg__DetectionArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // VEHICLE_MSGS__MSG__DETAIL__DETECTION_ARRAY__STRUCT_H_
