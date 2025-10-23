from launch import LaunchDescription
from launch_ros.actions import Node
# 封装终端指令相关类--------------
# from launch.actions import ExecuteProcess
# from launch.substitutions import FindExecutable
# 参数声明与获取-----------------
# from launch.actions import DeclareLaunchArgument
# from launch.substitutions import LaunchConfiguration
# 文件包含相关-------------------
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
# 分组相关----------------------
# from launch_ros.actions import PushRosNamespace
# from launch.actions import GroupAction
# 事件相关----------------------
# from launch.event_handlers import OnProcessStart, OnProcessExit
# from launch.actions import ExecuteProcess, RegisterEventHandler,LogInfo
# 获取功能包下share目录路径-------
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # imu_launch文件路径
    imu_launch_file = os.path.join(get_package_share_directory("senson_pkg"),
                                   "launch","senson_launch.py")
    # imu_launch文件包含
    # imu_launch = IncludeLaunchDescription(
    #     PythonLaunchDescriptionSource(imu_launch_file)
    # )
    # stm32_node节点
    stm32_node = Node(package="base_driver_pkg",executable="stm32_node",output="screen")
    # ekf.yaml文件路径
    ekf_node = Node(
    package='robot_localization',
    executable='ekf_node',
    name='ekf_filter_node',
    output='screen',
    parameters=[os.path.join(get_package_share_directory("localization_pkg"), 'params', 'ekf.yaml')]
    )

    return LaunchDescription([ekf_node,stm32_node])