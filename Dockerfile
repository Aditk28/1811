FROM ros:humble

ENV DEBIAN_FRONTEND=noninteractive
LABEL maintainer="1811"

RUN apt-get update && apt-get install -y \
    python3-pip \
    git \
    ros-humble-pcl-conversions \
    ros-humble-pcl-ros \
    git config --global --add safe.directory /vehicle_1811 \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /vehicle_1811