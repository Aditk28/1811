// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from vehicle_msgs:msg/Detection.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_MSGS__MSG__DETAIL__DETECTION__TRAITS_HPP_
#define VEHICLE_MSGS__MSG__DETAIL__DETECTION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "vehicle_msgs/msg/detail/detection__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace vehicle_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Detection & msg,
  std::ostream & out)
{
  out << "{";
  // member: label
  {
    out << "label: ";
    rosidl_generator_traits::value_to_yaml(msg.label, out);
    out << ", ";
  }

  // member: confidence
  {
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << ", ";
  }

  // member: x_min
  {
    out << "x_min: ";
    rosidl_generator_traits::value_to_yaml(msg.x_min, out);
    out << ", ";
  }

  // member: y_min
  {
    out << "y_min: ";
    rosidl_generator_traits::value_to_yaml(msg.y_min, out);
    out << ", ";
  }

  // member: x_max
  {
    out << "x_max: ";
    rosidl_generator_traits::value_to_yaml(msg.x_max, out);
    out << ", ";
  }

  // member: y_max
  {
    out << "y_max: ";
    rosidl_generator_traits::value_to_yaml(msg.y_max, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Detection & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: label
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "label: ";
    rosidl_generator_traits::value_to_yaml(msg.label, out);
    out << "\n";
  }

  // member: confidence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << "\n";
  }

  // member: x_min
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x_min: ";
    rosidl_generator_traits::value_to_yaml(msg.x_min, out);
    out << "\n";
  }

  // member: y_min
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y_min: ";
    rosidl_generator_traits::value_to_yaml(msg.y_min, out);
    out << "\n";
  }

  // member: x_max
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x_max: ";
    rosidl_generator_traits::value_to_yaml(msg.x_max, out);
    out << "\n";
  }

  // member: y_max
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y_max: ";
    rosidl_generator_traits::value_to_yaml(msg.y_max, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Detection & msg, bool use_flow_style = false)
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
  const vehicle_msgs::msg::Detection & msg,
  std::ostream & out, size_t indentation = 0)
{
  vehicle_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use vehicle_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const vehicle_msgs::msg::Detection & msg)
{
  return vehicle_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<vehicle_msgs::msg::Detection>()
{
  return "vehicle_msgs::msg::Detection";
}

template<>
inline const char * name<vehicle_msgs::msg::Detection>()
{
  return "vehicle_msgs/msg/Detection";
}

template<>
struct has_fixed_size<vehicle_msgs::msg::Detection>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<vehicle_msgs::msg::Detection>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<vehicle_msgs::msg::Detection>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // VEHICLE_MSGS__MSG__DETAIL__DETECTION__TRAITS_HPP_
