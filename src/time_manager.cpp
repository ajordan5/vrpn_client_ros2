
#include "vrpn_client_ros/time_manager.h"

namespace vrpn_client_ros
{

TimeManager::TimeManager() :
  min_offset_(0.0),
  count_(0)
{}

TimeManager::~TimeManager() {}

rclcpp::Time TimeManager::resolve_timestamp(const timeval& stamp, rclcpp::Node::SharedPtr nh)
{
  if (count_ >= num_samples_)
  {
    return mocap_to_ros_time(stamp) + offset_;
  }
  else
  {
    double offset_ns = nh->now().nanoseconds() - (stamp.tv_sec*pow(10, 9) + stamp.tv_usec*1000);

    if (count_ == 0 || offset_ns < min_offset_)
    {
      min_offset_ = offset_ns;
    }

    count_++;

    if (count_ == num_samples_)
    {
      RCLCPP_INFO_STREAM(nh->get_logger(), "Offset between Optitrack and ROS clocks: " << min_offset_);
      offset_ = rclcpp::Duration(min_offset_);
      count_++;
    }

    return nh->now();
  }
}

void TimeManager::set_num_samples(size_t num_samples)
{
  num_samples_ = num_samples;
}

rclcpp::Time TimeManager::mocap_to_ros_time(const timeval& stamp)
{
  return rclcpp::Time(stamp.tv_sec, stamp.tv_usec*1000);
}

} // namespace vrpn_client_ros
