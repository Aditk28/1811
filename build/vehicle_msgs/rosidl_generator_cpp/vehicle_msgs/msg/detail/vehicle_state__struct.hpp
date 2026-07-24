// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from vehicle_msgs:msg/VehicleState.idl
// generated code does not contain a copyright notice

#ifndef VEHICLE_MSGS__MSG__DETAIL__VEHICLE_STATE__STRUCT_HPP_
#define VEHICLE_MSGS__MSG__DETAIL__VEHICLE_STATE__STRUCT_HPP_

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
# define DEPRECATED__vehicle_msgs__msg__VehicleState __attribute__((deprecated))
#else
# define DEPRECATED__vehicle_msgs__msg__VehicleState __declspec(deprecated)
#endif

namespace vehicle_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VehicleState_
{
  using Type = VehicleState_<ContainerAllocator>;

  explicit VehicleState_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->speed_mps = 0.0f;
      this->battery_v = 0.0f;
      this->watchdog_tripped = false;
    }
  }

  explicit VehicleState_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->speed_mps = 0.0f;
      this->battery_v = 0.0f;
      this->watchdog_tripped = false;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _speed_mps_type =
    float;
  _speed_mps_type speed_mps;
  using _battery_v_type =
    float;
  _battery_v_type battery_v;
  using _watchdog_tripped_type =
    bool;
  _watchdog_tripped_type watchdog_tripped;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__speed_mps(
    const float & _arg)
  {
    this->speed_mps = _arg;
    return *this;
  }
  Type & set__battery_v(
    const float & _arg)
  {
    this->battery_v = _arg;
    return *this;
  }
  Type & set__watchdog_tripped(
    const bool & _arg)
  {
    this->watchdog_tripped = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    vehicle_msgs::msg::VehicleState_<ContainerAllocator> *;
  using ConstRawPtr =
    const vehicle_msgs::msg::VehicleState_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<vehicle_msgs::msg::VehicleState_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<vehicle_msgs::msg::VehicleState_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      vehicle_msgs::msg::VehicleState_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<vehicle_msgs::msg::VehicleState_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      vehicle_msgs::msg::VehicleState_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<vehicle_msgs::msg::VehicleState_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<vehicle_msgs::msg::VehicleState_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<vehicle_msgs::msg::VehicleState_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__vehicle_msgs__msg__VehicleState
    std::shared_ptr<vehicle_msgs::msg::VehicleState_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__vehicle_msgs__msg__VehicleState
    std::shared_ptr<vehicle_msgs::msg::VehicleState_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VehicleState_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->speed_mps != other.speed_mps) {
      return false;
    }
    if (this->battery_v != other.battery_v) {
      return false;
    }
    if (this->watchdog_tripped != other.watchdog_tripped) {
      return false;
    }
    return true;
  }
  bool operator!=(const VehicleState_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VehicleState_

// alias to use template instance with default allocator
using VehicleState =
  vehicle_msgs::msg::VehicleState_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace vehicle_msgs

#endif  // VEHICLE_MSGS__MSG__DETAIL__VEHICLE_STATE__STRUCT_HPP_
