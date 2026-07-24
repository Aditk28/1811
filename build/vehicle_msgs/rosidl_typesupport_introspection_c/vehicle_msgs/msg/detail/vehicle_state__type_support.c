// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from vehicle_msgs:msg/VehicleState.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "vehicle_msgs/msg/detail/vehicle_state__rosidl_typesupport_introspection_c.h"
#include "vehicle_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "vehicle_msgs/msg/detail/vehicle_state__functions.h"
#include "vehicle_msgs/msg/detail/vehicle_state__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void vehicle_msgs__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  vehicle_msgs__msg__VehicleState__init(message_memory);
}

void vehicle_msgs__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_fini_function(void * message_memory)
{
  vehicle_msgs__msg__VehicleState__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember vehicle_msgs__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_member_array[4] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_msgs__msg__VehicleState, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "speed_mps",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_msgs__msg__VehicleState, speed_mps),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "battery_v",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_msgs__msg__VehicleState, battery_v),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "watchdog_tripped",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(vehicle_msgs__msg__VehicleState, watchdog_tripped),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers vehicle_msgs__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_members = {
  "vehicle_msgs__msg",  // message namespace
  "VehicleState",  // message name
  4,  // number of fields
  sizeof(vehicle_msgs__msg__VehicleState),
  vehicle_msgs__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_member_array,  // message members
  vehicle_msgs__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_init_function,  // function to initialize message memory (memory has to be allocated)
  vehicle_msgs__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t vehicle_msgs__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_type_support_handle = {
  0,
  &vehicle_msgs__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_vehicle_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, vehicle_msgs, msg, VehicleState)() {
  vehicle_msgs__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!vehicle_msgs__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_type_support_handle.typesupport_identifier) {
    vehicle_msgs__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &vehicle_msgs__msg__VehicleState__rosidl_typesupport_introspection_c__VehicleState_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
