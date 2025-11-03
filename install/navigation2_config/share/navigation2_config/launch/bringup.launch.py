import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource

def generate_launch_description():

    map_server_pkg = get_package_share_directory("my_map_server")
    amcl_pkg = get_package_share_directory("localization_pkg")
    nav2_pkg = get_package_share_directory("navigation2_config")

    map_server_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(map_server_pkg,'launch',
                                                    'read_map_server.launch.py'))
        )

    amcl_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(amcl_pkg,'launch',
                                                    'mycar_amcl.launch.py'))
        )

    nav2_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(os.path.join(nav2_pkg,'launch', 
                                                    'nav2.launch.py'))
        )

    ld = LaunchDescription()
    ld.add_action(amcl_launch)
    ld.add_action(nav2_launch)
    ld.add_action(map_server_launch)
    return ld