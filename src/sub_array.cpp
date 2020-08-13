#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "ros2labview_examples/msg/intarray.hpp"


class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("array_sub")
  {
    subscription_ = this->create_subscription<ros2labview_examples::msg::Intarray>(
      "intarr", 10, [this](const ros2labview_examples::msg::Intarray::SharedPtr msg){
      RCLCPP_INFO(this->get_logger(), "I heard: %d %d %d", msg->num[0],msg->num[1],msg->num[2]);
    });
  }

private:
  rclcpp::Subscription<ros2labview_examples::msg::Intarray>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
