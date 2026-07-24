// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_msgs:msg/VehicleState.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_MSGS__MSG__DETAIL__VEHICLE_STATE__BUILDER_HPP_
#define VEHICLE_MSGS__MSG__DETAIL__VEHICLE_STATE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_msgs/msg/detail/vehicle_state__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_msgs
{

namespace msg
{

namespace builder
{

class Init_VehicleState_watchdog_tripped
{
public:
  explicit Init_VehicleState_watchdog_tripped(::vehicle_msgs::msg::VehicleState & msg)
  : msg_(msg)
  {}
  ::vehicle_msgs::msg::VehicleState watchdog_tripped(::vehicle_msgs::msg::VehicleState::_watchdog_tripped_type arg)
  {
    msg_.watchdog_tripped = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_msgs::msg::VehicleState msg_;
};

class Init_VehicleState_battery_v
{
public:
  explicit Init_VehicleState_battery_v(::vehicle_msgs::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_watchdog_tripped battery_v(::vehicle_msgs::msg::VehicleState::_battery_v_type arg)
  {
    msg_.battery_v = std::move(arg);
    return Init_VehicleState_watchdog_tripped(msg_);
  }

private:
  ::vehicle_msgs::msg::VehicleState msg_;
};

class Init_VehicleState_speed_mps
{
public:
  explicit Init_VehicleState_speed_mps(::vehicle_msgs::msg::VehicleState & msg)
  : msg_(msg)
  {}
  Init_VehicleState_battery_v speed_mps(::vehicle_msgs::msg::VehicleState::_speed_mps_type arg)
  {
    msg_.speed_mps = std::move(arg);
    return Init_VehicleState_battery_v(msg_);
  }

private:
  ::vehicle_msgs::msg::VehicleState msg_;
};

class Init_VehicleState_header
{
public:
  Init_VehicleState_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_VehicleState_speed_mps header(::vehicle_msgs::msg::VehicleState::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_VehicleState_speed_mps(msg_);
  }

private:
  ::vehicle_msgs::msg::VehicleState msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_msgs::msg::VehicleState>()
{
  return vehicle_msgs::msg::builder::Init_VehicleState_header();
}

}  // namespace vehicle_msgs

#endif  // VEHICLE_MSGS__MSG__DETAIL__VEHICLE_STATE__BUILDER_HPP_
