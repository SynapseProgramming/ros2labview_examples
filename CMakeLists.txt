cmake_minimum_required(VERSION 3.5)
project(ros2labview_examples)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#export(PACKAGE ros2labview_examples)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED) 

#generate the msg/srv header files
find_package(rosidl_default_generators REQUIRED)

rosidl_generate_interfaces(${PROJECT_NAME}
  "msg/Myint.msg"
  "msg/Clusterdemo.msg"
  "msg/Intarray.msg"
 )

# link against interface
rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp)



#add executables
add_executable(sub_int32 src/sub_int32.cpp)
ament_target_dependencies(sub_int32 rclcpp std_msgs)

add_executable(pub_int32 src/pub_int32.cpp)
ament_target_dependencies(pub_int32 rclcpp std_msgs)

add_executable(add_int src/add_int.cpp)
ament_target_dependencies(add_int rclcpp std_msgs)

add_executable(pub_custom_int src/pub_custom_int.cpp)
ament_target_dependencies(pub_custom_int rclcpp std_msgs )
target_link_libraries(pub_custom_int "${cpp_typesupport_target}")

add_executable(sub_custom_int src/sub_custom_int.cpp)
ament_target_dependencies(sub_custom_int rclcpp std_msgs )
target_link_libraries(sub_custom_int "${cpp_typesupport_target}")


add_executable(sub_cluster src/sub_cluster.cpp)
ament_target_dependencies(sub_cluster rclcpp std_msgs )
target_link_libraries(sub_cluster "${cpp_typesupport_target}")

add_executable(pub_cluster src/pub_cluster.cpp)
ament_target_dependencies(pub_cluster rclcpp std_msgs )
target_link_libraries(pub_cluster "${cpp_typesupport_target}")

add_executable(pub_array src/pub_array.cpp)
ament_target_dependencies(pub_array rclcpp std_msgs )
target_link_libraries(pub_array "${cpp_typesupport_target}")

add_executable(sub_array src/sub_array.cpp)
ament_target_dependencies(sub_array rclcpp std_msgs )
target_link_libraries(sub_array "${cpp_typesupport_target}")


#key in name here, for ro2 to find the executable
install(TARGETS
  pub_array
  sub_array
  pub_cluster 
  sub_cluster
  sub_int32
  pub_int32
  add_int
  pub_custom_int
  sub_custom_int
  DESTINATION lib/${PROJECT_NAME})






ament_package()
