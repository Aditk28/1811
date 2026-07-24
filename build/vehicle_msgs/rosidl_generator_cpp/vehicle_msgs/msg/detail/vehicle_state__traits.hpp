// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_msgs:msg/VehicleState.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_MSGS__MSG__DETAIL__VEHICLE_STATE__TRAITS_HPP_
#define VEHICLE_MSGS__MSG__DETAIL__VEHICLE_STATE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_msgs/msg/detail/vehicle_state__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace vehicle_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const VehicleState & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: speed_mps
  {
    out << "speed_mps: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_mps, out);
    out << ", ";
  }

  // member: battery_v
  {
    out << "battery_v: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_v, out);
    out << ", ";
  }

  // member: watchdog_tripped
  {
    out << "watchdog_tripped: ";
    rosidl_generator_traits::value_to_yaml(msg.watchdog_tripped, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VehicleState & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: speed_mps
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed_mps: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_mps, out);
    out << "\n";
  }

  // member: battery_v
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "battery_v: ";
    rosidl_generator_traits::value_to_yaml(msg.battery_v, out);
    out << "\n";
  }

  // member: watchdog_tripped
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "watchdog_tripped: ";
    rosidl_generator_traits::value_to_yaml(msg.watchdog_tripped, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VehicleState & msg, bool use_flow_style = false)
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

}  // namespace vehicle_msgs

namespace rosidl_generator_traits
{

[[deprecated("use vehicle_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const vehicle_msgs::msg::VehicleState & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_msgs::msg::VehicleState & msg)
{
  return vehicle_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_msgs::msg::VehicleState>()
{
  return "vehicle_msgs::msg::VehicleState";
}

template<>
inline const char * name<vehicle_msgs::msg::VehicleState>()
{
  return "vehicle_msgs/msg/VehicleState";
}

template<>
struct has_fixed_size<vehicle_msgs::msg::VehicleState>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<vehicle_msgs::msg::VehicleState>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<vehicle_msgs::msg::VehicleState>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_MSGS__MSG__DETAIL__VEHICLE_STATE__TRAITS_HPP_
