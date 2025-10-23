cmake_minimum_required(VERSION 3.8)
project(serial_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(serial_driver REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(base_interfaces REQUIRED)
find_package(nav_msgs REQUIRED)
# find_package(ros2launch REQUIRED)
# 假设你写的库代码放在 src/my_serial_lib.cpp，头文件在 include/cpp01_serial/my_serial_lib.hpp
add_library(my_serial_lib
  src/crc16.cpp
)
# 库需要包含头文件目录
target_include_directories(my_serial_lib PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
# 库的依赖
ament_target_dependencies(my_serial_lib
  "rclcpp"
)
  
# ---------------- 添加可执行文件 ----------------
add_executable(get_imu_ros2 src/get_imu_ros2.cpp)
add_executable(odom src/odom.cpp)
add_executable(chat_stm32 src/chat_stm32.cpp)
# 节点需要包含头文件目录
target_include_directories(get_imu_ros2 PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

target_compile_features(get_imu_ros2 PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
# 节点依赖  
ament_target_dependencies(
  get_imu_ros2
  "rclcpp"
  "serial_driver"
  "geometry_msgs"
  "sensor_msgs"
  "tf2"
  "tf2_ros"
  "base_interfaces"
)

ament_target_dependencies(
  odom
  "rclcpp"
  "serial_driver"
  "geometry_msgs"
  "sensor_msgs"
  "tf2"
  "tf2_ros"
  "base_interfaces"
  "nav_msgs"
)

ament_target_dependencies(
  chat_stm32
  "rclcpp"
  "serial_driver"
  "geometry_msgs"
  "base_interfaces"
)
# 让节点链接你写的库  nav_msgs geometry_msgs tf2_ros
target_link_libraries(get_imu_ros2 my_serial_lib)
target_link_libraries(chat_stm32 my_serial_lib)

# ---------------- 安装 ----------------
install(TARGETS 
  my_serial_lib
  get_imu_ros2
  odom
  chat_stm32
  DESTINATION lib/${PROJECT_NAME})

# install(DIRECTORY 
#   include/ 
#   DESTINATION include/
# )
install(DIRECTORY launch DESTINATION share/${PROJECT_NAME})
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




# cmake_minimum_required(VERSION 3.8)
# project(serial_pkg)

# if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   add_compile_options(-Wall -Wextra -Wpedantic)
# endif()

# # find dependencies
# find_package(ament_cmake REQUIRED)
# find_package(rclcpp REQUIRED)
# find_package(serial_driver REQUIRED)

# add_executable(get_imu_ros2 src/get_imu_ros2.cpp)
# target_include_directories(get_imu_ros2 PUBLIC
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#   $<INSTALL_INTERFACE:include>)
# target_compile_features(get_imu_ros2 PUBLIC c_std_99 cxx_std_17)  # Require C99 and C++17
# ament_target_dependencies(
#   get_imu_ros2
#   "rclcpp"
#   "serial_driver"
# )

# install(TARGETS get_imu_ros2
#   DESTINATION lib/${PROJECT_NAME})

# if(BUILD_TESTING)
#   find_package(ament_lint_auto REQUIRED)
#   # the following line skips the linter which checks for copyrights
#   # comment the line when a copyright and license is added to all source files
#   set(ament_cmake_copyright_FOUND TRUE)
#   # the following line skips cpplint (only works in a git repo)
#   # comment the line when this package is in a git repo and when
#   # a copyright and license is added to all source files
#   set(ament_cmake_cpplint_FOUND TRUE)
#   ament_lint_auto_find_test_dependencies()
# endif()

# ament_package()
