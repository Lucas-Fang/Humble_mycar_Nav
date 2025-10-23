from launch import LaunchDescription
from launch_ros.actions import Node
# 封装终端指令相关类--------------
# from launch.actions import ExecuteProcess
# from launch.substitutions import FindExecutable
# 参数声明与获取-----------------
# from launch.actions import DeclareLaunchArgument
# from launch.substitutions import LaunchConfiguration
# 文件包含相关-------------------
# from launch.actions import IncludeLaunchDescription
# from launch.launch_description_sources import PythonLaunchDescriptionSource
# 分组相关----------------------
# from launch_ros.actions import PushRosNamespace
# from launch.actions import GroupAction
# 事件相关----------------------
# from launch.event_handlers import OnProcessStart, OnProcessExit
# from launch.actions import ExecuteProcess, RegisterEventHandler,LogInfo
# 获取功能包下share目录路径-------
# from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    stm32_node = Node(
        package='base_driver_pkg',
        executable='stm32_node',
        name='stm32_node',
        output='screen',
    )
    odom_node = Node(
        package='base_driver_pkg',
        executable='odom_node',
        name='odom_node',
        output='screen',
    )
    # laser = Node(package='tf2_ros',executable='static_transform_publisher',name='base_to_laser_tf',
    #         output='screen',
    #         arguments=[
    #             '0.0',   # x 位置[m]
    #             '0.0',   # y 位置[m]
    #             '0.2',   # z 位置[m]
    #             '0',     # roll [rad]
    #             '0',     # pitch [rad]
    #             '0',     # yaw [rad]
    #             'base_link',  # 父坐标系
    #             'laser'       # 子坐标系
    #         ]
    #     )
    return LaunchDescription([stm32_node,odom_node])