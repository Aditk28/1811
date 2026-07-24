#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};


#[link(name = "vehicle_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__vehicle_msgs__msg__VehicleCommand() -> *const std::ffi::c_void;
}

#[link(name = "vehicle_msgs__rosidl_generator_c")]
extern "C" {
    fn vehicle_msgs__msg__VehicleCommand__init(msg: *mut VehicleCommand) -> bool;
    fn vehicle_msgs__msg__VehicleCommand__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<VehicleCommand>, size: usize) -> bool;
    fn vehicle_msgs__msg__VehicleCommand__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<VehicleCommand>);
    fn vehicle_msgs__msg__VehicleCommand__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<VehicleCommand>, out_seq: *mut rosidl_runtime_rs::Sequence<VehicleCommand>) -> bool;
}

// Corresponds to vehicle_msgs__msg__VehicleCommand
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct VehicleCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub throttle: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub steer: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub brake: f32,

}



impl Default for VehicleCommand {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !vehicle_msgs__msg__VehicleCommand__init(&mut msg as *mut _) {
        panic!("Call to vehicle_msgs__msg__VehicleCommand__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for VehicleCommand {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vehicle_msgs__msg__VehicleCommand__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vehicle_msgs__msg__VehicleCommand__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vehicle_msgs__msg__VehicleCommand__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for VehicleCommand {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for VehicleCommand where Self: Sized {
  const TYPE_NAME: &'static str = "vehicle_msgs/msg/VehicleCommand";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__vehicle_msgs__msg__VehicleCommand() }
  }
}


#[link(name = "vehicle_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__vehicle_msgs__msg__VehicleState() -> *const std::ffi::c_void;
}

#[link(name = "vehicle_msgs__rosidl_generator_c")]
extern "C" {
    fn vehicle_msgs__msg__VehicleState__init(msg: *mut VehicleState) -> bool;
    fn vehicle_msgs__msg__VehicleState__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<VehicleState>, size: usize) -> bool;
    fn vehicle_msgs__msg__VehicleState__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<VehicleState>);
    fn vehicle_msgs__msg__VehicleState__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<VehicleState>, out_seq: *mut rosidl_runtime_rs::Sequence<VehicleState>) -> bool;
}

// Corresponds to vehicle_msgs__msg__VehicleState
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct VehicleState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub speed_mps: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub battery_v: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub watchdog_tripped: bool,

}



impl Default for VehicleState {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !vehicle_msgs__msg__VehicleState__init(&mut msg as *mut _) {
        panic!("Call to vehicle_msgs__msg__VehicleState__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for VehicleState {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vehicle_msgs__msg__VehicleState__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vehicle_msgs__msg__VehicleState__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vehicle_msgs__msg__VehicleState__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for VehicleState {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for VehicleState where Self: Sized {
  const TYPE_NAME: &'static str = "vehicle_msgs/msg/VehicleState";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__vehicle_msgs__msg__VehicleState() }
  }
}


#[link(name = "vehicle_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__vehicle_msgs__msg__Detection() -> *const std::ffi::c_void;
}

#[link(name = "vehicle_msgs__rosidl_generator_c")]
extern "C" {
    fn vehicle_msgs__msg__Detection__init(msg: *mut Detection) -> bool;
    fn vehicle_msgs__msg__Detection__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<Detection>, size: usize) -> bool;
    fn vehicle_msgs__msg__Detection__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<Detection>);
    fn vehicle_msgs__msg__Detection__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<Detection>, out_seq: *mut rosidl_runtime_rs::Sequence<Detection>) -> bool;
}

// Corresponds to vehicle_msgs__msg__Detection
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Detection {

    // This member is not documented.
    #[allow(missing_docs)]
    pub label: rosidl_runtime_rs::String,


    // This member is not documented.
    #[allow(missing_docs)]
    pub confidence: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub x_min: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub y_min: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub x_max: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub y_max: f32,

}



impl Default for Detection {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !vehicle_msgs__msg__Detection__init(&mut msg as *mut _) {
        panic!("Call to vehicle_msgs__msg__Detection__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for Detection {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vehicle_msgs__msg__Detection__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vehicle_msgs__msg__Detection__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vehicle_msgs__msg__Detection__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for Detection {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for Detection where Self: Sized {
  const TYPE_NAME: &'static str = "vehicle_msgs/msg/Detection";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__vehicle_msgs__msg__Detection() }
  }
}


#[link(name = "vehicle_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__vehicle_msgs__msg__DetectionArray() -> *const std::ffi::c_void;
}

#[link(name = "vehicle_msgs__rosidl_generator_c")]
extern "C" {
    fn vehicle_msgs__msg__DetectionArray__init(msg: *mut DetectionArray) -> bool;
    fn vehicle_msgs__msg__DetectionArray__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<DetectionArray>, size: usize) -> bool;
    fn vehicle_msgs__msg__DetectionArray__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<DetectionArray>);
    fn vehicle_msgs__msg__DetectionArray__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<DetectionArray>, out_seq: *mut rosidl_runtime_rs::Sequence<DetectionArray>) -> bool;
}

// Corresponds to vehicle_msgs__msg__DetectionArray
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DetectionArray {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::rmw::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub detections: rosidl_runtime_rs::Sequence<super::super::msg::rmw::Detection>,

}



impl Default for DetectionArray {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !vehicle_msgs__msg__DetectionArray__init(&mut msg as *mut _) {
        panic!("Call to vehicle_msgs__msg__DetectionArray__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for DetectionArray {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vehicle_msgs__msg__DetectionArray__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vehicle_msgs__msg__DetectionArray__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { vehicle_msgs__msg__DetectionArray__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for DetectionArray {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for DetectionArray where Self: Sized {
  const TYPE_NAME: &'static str = "vehicle_msgs/msg/DetectionArray";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__vehicle_msgs__msg__DetectionArray() }
  }
}


