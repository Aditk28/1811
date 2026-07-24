// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_msgs:msg/VehicleCommand.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_MSGS__MSG__DETAIL__VEHICLE_COMMAND__STRUCT_HPP_
#define VEHICLE_MSGS__MSG__DETAIL__VEHICLE_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__vehicle_msgs__msg__VehicleCommand __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_msgs__msg__VehicleCommand __declspec(deprecated)
#endif

namespace vehicle_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VehicleCommand_
{
  using Type = VehicleCommand_<ContainerAllocator>;

  explicit VehicleCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->throttle = 0.0f;
      this->steer = 0.0f;
      this->brake = 0.0f;
    }
  }

  explicit VehicleCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->throttle = 0.0f;
      this->steer = 0.0f;
      this->brake = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _throttle_type =
    float;
  _throttle_type throttle;
  using _steer_type =
    float;
  _steer_type steer;
  using _brake_type =
    float;
  _brake_type brake;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__throttle(
    const float & _arg)
  {
    this->throttle = _arg;
    return *this;
  }
  Type & set__steer(
    const float & _arg)
  {
    this->steer = _arg;
    return *this;
  }
  Type & set__brake(
    const float & _arg)
  {
    this->brake = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_msgs::msg::VehicleCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_msgs::msg::VehicleCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_msgs::msg::VehicleCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_msgs::msg::VehicleCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_msgs::msg::VehicleCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_msgs::msg::VehicleCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_msgs::msg::VehicleCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_msgs::msg::VehicleCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_msgs::msg::VehicleCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_msgs::msg::VehicleCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_msgs__msg__VehicleCommand
    std::shared_ptr<vehicle_msgs::msg::VehicleCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_msgs__msg__VehicleCommand
    std::shared_ptr<vehicle_msgs::msg::VehicleCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VehicleCommand_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->throttle != other.throttle) {
      return false;
    }
    if (this->steer != other.steer) {
      return false;
    }
    if (this->brake != other.brake) {
      return false;
    }
    return true;
  }
  bool operator!=(const VehicleCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VehicleCommand_

// alias to use template instance with default allocator
using VehicleCommand =
  vehicle_msgs::msg::VehicleCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_msgs

#endif  // VEHICLE_MSGS__MSG__DETAIL__VEHICLE_COMMAND__STRUCT_HPP_
