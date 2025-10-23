cmake_minimum_required(VERSION 3.8)
project(base_driver_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(serial_driver REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)

add_executable(stm32_node src/stm32_node.cpp)
add_executable(odom_node src/odom_node.cpp)
add_executable(pub_cmd_vel_to_classic src/pub_cmd_vel_to_classic.cpp)

target_include_directories(stm32_node PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
target_compile_features(stm32_node PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
ament_target_dependencies(
  stm32_node
  "rclcpp"
  "serial_driver"
  "geometry_msgs"
  "tf2"
  "tf2_ros"
  "nav_msgs"
)
ament_target_dependencies(
  odom_node
  "rclcpp"
  "geometry_msgs"
  "tf2"
  "tf2_ros"
  "nav_msgs"
  "sensor_msgs"
)

ament_target_dependencies(
  pub_cmd_vel_to_classic
  "rclcpp"
  "geometry_msgs"
  "serial_driver"
)

install(TARGETS 
  stm32_node 
  odom_node
  pub_cmd_vel_to_classic
  DESTINATION lib/${PROJECT_NAME})

install(DIRECTORY launch 
  DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
