#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to vehicle_msgs__msg__VehicleCommand

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct VehicleCommand {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::VehicleCommand::default())
  }
}

impl rosidl_runtime_rs::Message for VehicleCommand {
  type RmwMsg = super::msg::rmw::VehicleCommand;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        throttle: msg.throttle,
        steer: msg.steer,
        brake: msg.brake,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      throttle: msg.throttle,
      steer: msg.steer,
      brake: msg.brake,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      throttle: msg.throttle,
      steer: msg.steer,
      brake: msg.brake,
    }
  }
}


// Corresponds to vehicle_msgs__msg__VehicleState

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct VehicleState {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::VehicleState::default())
  }
}

impl rosidl_runtime_rs::Message for VehicleState {
  type RmwMsg = super::msg::rmw::VehicleState;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        speed_mps: msg.speed_mps,
        battery_v: msg.battery_v,
        watchdog_tripped: msg.watchdog_tripped,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      speed_mps: msg.speed_mps,
      battery_v: msg.battery_v,
      watchdog_tripped: msg.watchdog_tripped,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      speed_mps: msg.speed_mps,
      battery_v: msg.battery_v,
      watchdog_tripped: msg.watchdog_tripped,
    }
  }
}


// Corresponds to vehicle_msgs__msg__Detection

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Detection {

    // This member is not documented.
    #[allow(missing_docs)]
    pub label: std::string::String,


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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Detection::default())
  }
}

impl rosidl_runtime_rs::Message for Detection {
  type RmwMsg = super::msg::rmw::Detection;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        label: msg.label.as_str().into(),
        confidence: msg.confidence,
        x_min: msg.x_min,
        y_min: msg.y_min,
        x_max: msg.x_max,
        y_max: msg.y_max,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        label: msg.label.as_str().into(),
      confidence: msg.confidence,
      x_min: msg.x_min,
      y_min: msg.y_min,
      x_max: msg.x_max,
      y_max: msg.y_max,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      label: msg.label.to_string(),
      confidence: msg.confidence,
      x_min: msg.x_min,
      y_min: msg.y_min,
      x_max: msg.x_max,
      y_max: msg.y_max,
    }
  }
}


// Corresponds to vehicle_msgs__msg__DetectionArray

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct DetectionArray {

    // This member is not documented.
    #[allow(missing_docs)]
    pub header: std_msgs::msg::Header,


    // This member is not documented.
    #[allow(missing_docs)]
    pub detections: Vec<super::msg::Detection>,

}



impl Default for DetectionArray {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::DetectionArray::default())
  }
}

impl rosidl_runtime_rs::Message for DetectionArray {
  type RmwMsg = super::msg::rmw::DetectionArray;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
        detections: msg.detections
          .into_iter()
          .map(|elem| super::msg::Detection::into_rmw_message(std::borrow::Cow::Owned(elem)).into_owned())
          .collect(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
        detections: msg.detections
          .iter()
          .map(|elem| super::msg::Detection::into_rmw_message(std::borrow::Cow::Borrowed(elem)).into_owned())
          .collect(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
      detections: msg.detections
          .into_iter()
          .map(super::msg::Detection::from_rmw_message)
          .collect(),
    }
  }
}


