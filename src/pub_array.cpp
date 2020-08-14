
// common stl includes
#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "ros2labview_examples/msg/intarray.hpp"

using namespace std::chrono_literals;


class MinimalPublisher : public rclcpp::Node
{
public:

  MinimalPublisher()
  : Node("ros_publisher")
  {
    publisher_ = this->create_publisher<ros2labview_examples::msg::Intarray>("intarr", 10);

    //init the timer ptr with a wall timer object.

    timer_ = this->create_wall_timer(
      500ms, [this](){
        // create string obj.
        auto message = ros2labview_examples::msg::Intarray();
        message.num.push_back(this->count);
        message.num.push_back((this->count)+10);
        message.num.push_back((this->count)+100);

        RCLCPP_INFO(this->get_logger(), "Publishing: %d %d %d", message.num[0], message.num[1],message.num[2]);
        //publish message
        publisher_->publish(message);
        this->count++;
      });
  }

private:
  int count=0;
  //shared ptr of a timer
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<ros2labview_examples::msg::Intarray>::SharedPtr publisher_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
