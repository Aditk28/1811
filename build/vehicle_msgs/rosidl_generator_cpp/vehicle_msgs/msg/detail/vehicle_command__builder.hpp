// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_msgs:msg/VehicleCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_MSGS__MSG__DETAIL__VEHICLE_COMMAND__BUILDER_HPP_
#define VEHICLE_MSGS__MSG__DETAIL__VEHICLE_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_msgs/msg/detail/vehicle_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_msgs
{

namespace msg
{

namespace builder
{

class Init_VehicleCommand_brake
{
public:
  explicit Init_VehicleCommand_brake(::vehicle_msgs::msg::VehicleCommand & msg)
  : msg_(msg)
  {}
  ::vehicle_msgs::msg::VehicleCommand brake(::vehicle_msgs::msg::VehicleCommand::_brake_type arg)
  {
    msg_.brake = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_msgs::msg::VehicleCommand msg_;
};

class Init_VehicleCommand_steer
{
public:
  explicit Init_VehicleCommand_steer(::vehicle_msgs::msg::VehicleCommand & msg)
  : msg_(msg)
  {}
  Init_VehicleCommand_brake steer(::vehicle_msgs::msg::VehicleCommand::_steer_type arg)
  {
    msg_.steer = std::move(arg);
    return Init_VehicleCommand_brake(msg_);
  }

private:
  ::vehicle_msgs::msg::VehicleCommand msg_;
};

class Init_VehicleCommand_throttle
{
public:
  explicit Init_VehicleCommand_throttle(::vehicle_msgs::msg::VehicleCommand & msg)
  : msg_(msg)
  {}
  Init_VehicleCommand_steer throttle(::vehicle_msgs::msg::VehicleCommand::_throttle_type arg)
  {
    msg_.throttle = std::move(arg);
    return Init_VehicleCommand_steer(msg_);
  }

private:
  ::vehicle_msgs::msg::VehicleCommand msg_;
};

class Init_VehicleCommand_header
{
public:
  Init_VehicleCommand_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleCommand_throttle header(::vehicle_msgs::msg::VehicleCommand::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_VehicleCommand_throttle(msg_);
  }

private:
  ::vehicle_msgs::msg::VehicleCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_msgs::msg::VehicleCommand>()
{
  return vehicle_msgs::msg::builder::Init_VehicleCommand_header();
}

}  // namespace vehicle_msgs

#endif  // VEHICLE_MSGS__MSG__DETAIL__VEHICLE_COMMAND__BUILDER_HPP_
