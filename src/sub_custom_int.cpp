#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "ros2labview_examples/msg/myint.hpp"


class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("cint_sub")
  {
    subscription_ = this->create_subscription<ros2labview_examples::msg::Myint>(
      "clabint", 10, [this](const ros2labview_examples::msg::Myint::SharedPtr msg){
      RCLCPP_INFO(this->get_logger(), "I heard: %d", msg->num);
    });
  }

private:
  rclcpp::Subscription<ros2labview_examples::msg::Myint>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
