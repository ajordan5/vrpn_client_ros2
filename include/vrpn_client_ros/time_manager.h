#ifndef VRPN_CLIENT_ROS2_TIME_MANAGER_H
#define VRPN_CLIENT_ROS2_TIME_MANAGER_H

#include "rclcpp/rclcpp.hpp"

namespace vrpn_client_ros
{

class TimeManager
{
public:
    TimeManager();
    ~TimeManager();
    rclcpp::Time resolve_timestamp(const timeval& mocap_time, rclcpp::Node::SharedPtr nh);
    void set_num_samples(size_t);

private:
    double min_offset_;
    size_t count_;
    size_t num_samples_=100;

    rclcpp::Duration offset_ = rclcpp::Duration(0.0);

    rclcpp::Time mocap_to_ros_time(const timeval& mocap_time);
};

}

#endif