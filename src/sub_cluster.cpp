#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "ros2labview_examples/msg/clusterdemo.hpp"


class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("cluster_sub")
  {
    subscription_ = this->create_subscription<ros2labview_examples::msg::Clusterdemo>(
      "intcust", 10, [this](const ros2labview_examples::msg::Clusterdemo::SharedPtr msg){
      RCLCPP_INFO(this->get_logger(), "I heard: %d and %d", msg->x,msg->y);
    });
  }

private:
  rclcpp::Subscription<ros2labview_examples::msg::Clusterdemo>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
