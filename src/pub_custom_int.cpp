
// common stl includes
#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "ros2labview_examples/msg/myint.hpp"

using namespace std::chrono_literals;


class MinimalPublisher : public rclcpp::Node
{
public:

  MinimalPublisher()
  : Node("ros_publisher")
  {
    publisher_ = this->create_publisher<ros2labview_examples::msg::Myint>("rosint", 10);

    //init the timer ptr with a wall timer object.

    timer_ = this->create_wall_timer(
      500ms, [this](){
        // create string obj.
        auto message = ros2labview_examples::msg::Myint();
        message.num = this->count;
        RCLCPP_INFO(this->get_logger(), "Publishing: '%d'", message.num);
        //publish message
        publisher_->publish(message);
        this->count++;
      });
  }

private:
  int count=0;
  //shared ptr of a timer
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<ros2labview_examples::msg::Myint>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
