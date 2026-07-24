// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from vehicle_msgs:msg/Detection.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_MSGS__MSG__DETAIL__DETECTION__BUILDER_HPP_
#define VEHICLE_MSGS__MSG__DETAIL__DETECTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "vehicle_msgs/msg/detail/detection__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace vehicle_msgs
{

namespace msg
{

namespace builder
{

class Init_Detection_y_max
{
public:
  explicit Init_Detection_y_max(::vehicle_msgs::msg::Detection & msg)
  : msg_(msg)
  {}
  ::vehicle_msgs::msg::Detection y_max(::vehicle_msgs::msg::Detection::_y_max_type arg)
  {
    msg_.y_max = std::move(arg);
    return std::move(msg_);
  }

private:
  ::vehicle_msgs::msg::Detection msg_;
};

class Init_Detection_x_max
{
public:
  explicit Init_Detection_x_max(::vehicle_msgs::msg::Detection & msg)
  : msg_(msg)
  {}
  Init_Detection_y_max x_max(::vehicle_msgs::msg::Detection::_x_max_type arg)
  {
    msg_.x_max = std::move(arg);
    return Init_Detection_y_max(msg_);
  }

private:
  ::vehicle_msgs::msg::Detection msg_;
};

class Init_Detection_y_min
{
public:
  explicit Init_Detection_y_min(::vehicle_msgs::msg::Detection & msg)
  : msg_(msg)
  {}
  Init_Detection_x_max y_min(::vehicle_msgs::msg::Detection::_y_min_type arg)
  {
    msg_.y_min = std::move(arg);
    return Init_Detection_x_max(msg_);
  }

private:
  ::vehicle_msgs::msg::Detection msg_;
};

class Init_Detection_x_min
{
public:
  explicit Init_Detection_x_min(::vehicle_msgs::msg::Detection & msg)
  : msg_(msg)
  {}
  Init_Detection_y_min x_min(::vehicle_msgs::msg::Detection::_x_min_type arg)
  {
    msg_.x_min = std::move(arg);
    return Init_Detection_y_min(msg_);
  }

private:
  ::vehicle_msgs::msg::Detection msg_;
};

class Init_Detection_confidence
{
public:
  explicit Init_Detection_confidence(::vehicle_msgs::msg::Detection & msg)
  : msg_(msg)
  {}
  Init_Detection_x_min confidence(::vehicle_msgs::msg::Detection::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return Init_Detection_x_min(msg_);
  }

private:
  ::vehicle_msgs::msg::Detection msg_;
};

class Init_Detection_label
{
public:
  Init_Detection_label()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Detection_confidence label(::vehicle_msgs::msg::Detection::_label_type arg)
  {
    msg_.label = std::move(arg);
    return Init_Detection_confidence(msg_);
  }

private:
  ::vehicle_msgs::msg::Detection msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::vehicle_msgs::msg::Detection>()
{
  return vehicle_msgs::msg::builder::Init_Detection_label();
}

}  // namespace vehicle_msgs

#endif  // VEHICLE_MSGS__MSG__DETAIL__DETECTION__BUILDER_HPP_
