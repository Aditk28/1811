// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_msgs:msg/DetectionArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_msgs/msg/detail/detection_array__rosidl_typesupport_introspection_c.h"
#include "vehicle_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_msgs/msg/detail/detection_array__functions.h"
#include "vehicle_msgs/msg/detail/detection_array__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `detections`
#include "vehicle_msgs/msg/detection.h"
// Member `detections`
#include "vehicle_msgs/msg/detail/detection__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__DetectionArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_msgs__msg__DetectionArray__init(message_memory);
}

void vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__DetectionArray_fini_function(void * message_memory)
{
  vehicle_msgs__msg__DetectionArray__fini(message_memory);
}

size_t vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__size_function__DetectionArray__detections(
  const void * untyped_member)
{
  const vehicle_msgs__msg__Detection__Sequence * member =
    (const vehicle_msgs__msg__Detection__Sequence *)(untyped_member);
  return member->size;
}

const void * vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__get_const_function__DetectionArray__detections(
  const void * untyped_member, size_t index)
{
  const vehicle_msgs__msg__Detection__Sequence * member =
    (const vehicle_msgs__msg__Detection__Sequence *)(untyped_member);
  return &member->data[index];
}

void * vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__get_function__DetectionArray__detections(
  void * untyped_member, size_t index)
{
  vehicle_msgs__msg__Detection__Sequence * member =
    (vehicle_msgs__msg__Detection__Sequence *)(untyped_member);
  return &member->data[index];
}

void vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__fetch_function__DetectionArray__detections(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const vehicle_msgs__msg__Detection * item =
    ((const vehicle_msgs__msg__Detection *)
    vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__get_const_function__DetectionArray__detections(untyped_member, index));
  vehicle_msgs__msg__Detection * value =
    (vehicle_msgs__msg__Detection *)(untyped_value);
  *value = *item;
}

void vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__assign_function__DetectionArray__detections(
  void * untyped_member, size_t index, const void * untyped_value)
{
  vehicle_msgs__msg__Detection * item =
    ((vehicle_msgs__msg__Detection *)
    vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__get_function__DetectionArray__detections(untyped_member, index));
  const vehicle_msgs__msg__Detection * value =
    (const vehicle_msgs__msg__Detection *)(untyped_value);
  *item = *value;
}

bool vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__resize_function__DetectionArray__detections(
  void * untyped_member, size_t size)
{
  vehicle_msgs__msg__Detection__Sequence * member =
    (vehicle_msgs__msg__Detection__Sequence *)(untyped_member);
  vehicle_msgs__msg__Detection__Sequence__fini(member);
  return vehicle_msgs__msg__Detection__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__DetectionArray_message_member_array[2] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_msgs__msg__DetectionArray, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "detections",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_msgs__msg__DetectionArray, detections),  // bytes offset in struct
    NULL,  // default value
    vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__size_function__DetectionArray__detections,  // size() function pointer
    vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__get_const_function__DetectionArray__detections,  // get_const(index) function pointer
    vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__get_function__DetectionArray__detections,  // get(index) function pointer
    vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__fetch_function__DetectionArray__detections,  // fetch(index, &value) function pointer
    vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__assign_function__DetectionArray__detections,  // assign(index, value) function pointer
    vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__resize_function__DetectionArray__detections  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__DetectionArray_message_members = {
  "vehicle_msgs__msg",  // message namespace
  "DetectionArray",  // message name
  2,  // number of fields
  sizeof(vehicle_msgs__msg__DetectionArray),
  vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__DetectionArray_message_member_array,  // message members
  vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__DetectionArray_init_function,  // function to initialize message memory (memory has to be allocated)
  vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__DetectionArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__DetectionArray_message_type_support_handle = {
  0,
  &vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__DetectionArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_msgs, msg, DetectionArray)() {
  vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__DetectionArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__DetectionArray_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_msgs, msg, Detection)();
  if (!vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__DetectionArray_message_type_support_handle.typesupport_identifier) {
    vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__DetectionArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vehicle_msgs__msg__DetectionArray__rosidl_typesupport_introspection_c__DetectionArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
