#ifndef __IMU_DRIVER_HPP_ 
#define __IMU_DRIVER_HPP_


#include "rclcpp/rclcpp.hpp"
// #include <filesystem>
#include <memory>
#include "senson_pkg/crc16.h"


typedef struct
{
    float accx;
    float accy;
    float accz;
    float gyrox;
    float gyroy;
    float gyroz;
    float roll;
    float pitch;
    float yaw;
}IMU_Data;
struct Quaternion {
  float w;  // 实部（标量部分）
  float x;  // 虚部（i轴分量）
  float y;  // 虚部（j轴分量）
  float z;  // 虚部（k轴分量）
};

class IMUDriver
{
public:
    // IMUDriver();
    // ~IMUDriver();    
    IMU_Data get_imu_data(std::vector<uint8_t> recv_buffer_) ;   
private:
    IMU_Data imu{};
    struct Quaternion q;
};

#endif