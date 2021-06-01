#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"

#define be RMW_QOS_POLICY_RELIABILITY_BEST_EFFORT

class PubSub : public rclcpp::Node
{
public:

  PubSub()
  : Node("ros_addint"),
    best_effort(rclcpp::KeepLast(10))
  {
    auto int_callback= [this](const std_msgs::msg::Int32::SharedPtr msg){
      auto to_add=std_msgs::msg::Int32();
      to_add.data=msg->data;
      to_add.data+=10;
      RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", to_add.data);
      publisher_->publish(to_add);
    };

    publisher_ = this->create_publisher<std_msgs::msg::Int32>("result", 10);
    subscription_ = this->create_subscription<std_msgs::msg::Int32>("toadd",best_effort.reliability(be),int_callback);

  }
HEHE THIS IS MADE TO CRASH THE PROGRAM
private:

  //shared ptr of a timer
  rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;

  rclcpp::QoS best_effort;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PubSub>());
  rclcpp::shutdown();
  return 0;
}
