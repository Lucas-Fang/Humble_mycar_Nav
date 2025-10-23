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
# from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    get_imu_node = Node( package='serial_pkg',executable='get_imu_ros2',
                        name='get_imu_node',output='screen',)
    chat_stm32_node = Node(package='serial_pkg',executable='chat_stm32',
                        name='chat_stm32_node',output='screen',)
    cala_odom_node = Node(package='serial_pkg',executable='odom',
                        name='cala_odom_node',output='screen',)
    
    return LaunchDescription([get_imu_node,chat_stm32_node,cala_odom_node])