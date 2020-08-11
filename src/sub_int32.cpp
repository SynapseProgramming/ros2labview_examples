#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"


class MinimalSubscriber : public rclcpp::Node
{
public:
  MinimalSubscriber()
  : Node("int_sub")
  {
    subscription_ = this->create_subscription<std_msgs::msg::Int32>(
      "labviewint", 10, [this](const std_msgs::msg::Int32::SharedPtr msg){
      RCLCPP_INFO(this->get_logger(), "I heard: %d", msg->data);
    });
  }

private:
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalSubscriber>());
  rclcpp::shutdown();
  return 0;
}
