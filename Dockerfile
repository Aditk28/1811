FROM ros:humble

ENV DEBIAN_FRONTEND=noninteractive
LABEL maintainer="1811"

RUN apt-get update && apt-get install -y \
    python3-pip \
    git \
    ros-humble-pcl-conversions \
    ros-humble-pcl-ros \
    ros-humble-tf2-eigen \
    ros-humble-rviz2 \
    ros-humble-xacro \
    ros-humble-robot-state-publisher \
    ros-humble-joint-state-publisher \
    ros-humble-joint-state-publisher-gui \
    ros-humble-tf2-tools \
    build-essential \
    libeigen3-dev \
    libjsoncpp-dev \
    libspdlog-dev \
    libcurl4-openssl-dev \
    libopencv-dev \
    libzip-dev \
    libssl-dev \
    cmake \
    python3-colcon-common-extensions \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN git config --global --add safe.directory /vehicle_1811

WORKDIR /vehicle_1811