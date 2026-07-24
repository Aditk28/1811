// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_msgs:msg/VehicleCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_MSGS__MSG__DETAIL__VEHICLE_COMMAND__TRAITS_HPP_
#define VEHICLE_MSGS__MSG__DETAIL__VEHICLE_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_msgs/msg/detail/vehicle_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace vehicle_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const VehicleCommand & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: throttle
  {
    out << "throttle: ";
    rosidl_generator_traits::value_to_yaml(msg.throttle, out);
    out << ", ";
  }

  // member: steer
  {
    out << "steer: ";
    rosidl_generator_traits::value_to_yaml(msg.steer, out);
    out << ", ";
  }

  // member: brake
  {
    out << "brake: ";
    rosidl_generator_traits::value_to_yaml(msg.brake, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const VehicleCommand & msg,
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

  // member: throttle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "throttle: ";
    rosidl_generator_traits::value_to_yaml(msg.throttle, out);
    out << "\n";
  }

  // member: steer
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "steer: ";
    rosidl_generator_traits::value_to_yaml(msg.steer, out);
    out << "\n";
  }

  // member: brake
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "brake: ";
    rosidl_generator_traits::value_to_yaml(msg.brake, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const VehicleCommand & msg, bool use_flow_style = false)
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
  const vehicle_msgs::msg::VehicleCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_msgs::msg::VehicleCommand & msg)
{
  return vehicle_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_msgs::msg::VehicleCommand>()
{
  return "vehicle_msgs::msg::VehicleCommand";
}

template<>
inline const char * name<vehicle_msgs::msg::VehicleCommand>()
{
  return "vehicle_msgs/msg/VehicleCommand";
}

template<>
struct has_fixed_size<vehicle_msgs::msg::VehicleCommand>
  : std::integral_constant<bool, has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<vehicle_msgs::msg::VehicleCommand>
  : std::integral_constant<bool, has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<vehicle_msgs::msg::VehicleCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_MSGS__MSG__DETAIL__VEHICLE_COMMAND__TRAITS_HPP_
