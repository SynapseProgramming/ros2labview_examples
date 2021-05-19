#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "ros2labview_examples/msg/clusterdemo.hpp"

#define be RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT

class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("cluster_sub"),
    best_effort(rclcpp::KeepLast(10))
  {
    subscription_ = this->create_subscription<ros2labview_examples::msg::Clusterdemo>(
      "intcust", best_effort.reliability(be), [this](const ros2labview_examples::msg::Clusterdemo::SharedPtr msg){
      RCLCPP_INFO(this->get_logger(), "I heard: %d and %d", msg->x,msg->y);
    });
  }

private:
  rclcpp::Subscription<ros2labview_examples::msg::Clusterdemo>::SharedPtr subscription_;

  rclcpp::QoS best_effort;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
