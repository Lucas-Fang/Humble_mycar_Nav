#include "rclcpp/rclcpp.hpp"
#include "senson_pkg/imu_driver.hpp"

IMU_Data IMUDriver::get_imu_data(std::vector<uint8_t> recv_buffer_)  //创建一个函数更方便重新调用
{
    while (recv_buffer_.size() >= 19) { // 至少一帧
            // 找帧头
            if (recv_buffer_[0] != 0x55 || recv_buffer_[1] != 0xAA) {
                recv_buffer_.erase(recv_buffer_.begin());
                continue;
            }
            if (recv_buffer_[3] == 0x04) {
            std::vector<uint8_t> frame(recv_buffer_.begin(), recv_buffer_.begin() + 23);
            uint16_t crc_in_frame = (uint16_t)frame[20] | ((uint16_t)frame[21] << 8);
            uint16_t crc_calc = imu_driver::Get_CRC16(frame.data(), 20);
            if (crc_in_frame == crc_calc){
                
                std::memcpy(&q.x, &frame[4], 4);
                std::memcpy(&q.y, &frame[8], 4);
                std::memcpy(&q.z, &frame[12],4);
                std::memcpy(&q.w, &frame[16],4);
                };
            }
            // 取一帧
            std::vector<uint8_t> frame(recv_buffer_.begin(), recv_buffer_.begin() + 19);

            // 校验 CRC16
            uint16_t crc_in_frame = (uint16_t)frame[16] | ((uint16_t)frame[17] << 8);
            uint16_t crc_calc = imu_driver::Get_CRC16(frame.data(), 16);
            
            if (crc_in_frame == crc_calc) {
            switch (frame[3])
            {
                case 0x01: // 加速度
                    std::memcpy(&imu.accx,  &frame[4], 4);
                    std::memcpy(&imu.accy, &frame[8], 4);
                    std::memcpy(&imu.accz,   &frame[12],4);
                    // RCLCPP_INFO(this->get_logger(),
                    //     "IMU Acc: ax=%.2f, ay=%.2f, az=%.2f",
                    //     imu.accx, imu.accy, imu.accz);
                    break;
                case 0x02: // 角速度
                    std::memcpy(&imu.gyrox,  &frame[4], 4);
                    std::memcpy(&imu.gyroy, &frame[8], 4);
                    std::memcpy(&imu.gyroz,   &frame[12],4);
                    // RCLCPP_INFO(this->get_logger(),
                    //     "IMU Gyro: gx=%.2f, gy=%.2f, gz=%.2f",
                    //     imu.gyrox, imu.gyroy, imu.gyroz);
                    break;
                case 0x03: // 姿态角
                    std::memcpy(&imu.roll,  &frame[4], 4);
                    std::memcpy(&imu.pitch, &frame[8], 4);
                    std::memcpy(&imu.yaw,   &frame[12],4);
                    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
                        "IMU RPY: roll=%.2f, pitch=%.2f, yaw=%.2f",
                        imu.roll, imu.pitch, imu.yaw);
                    break;

                default:
                    break;
            }
            } else {
                // RCLCPP_WARN(this->get_logger(), "CRC mismatch, drop frame");
            }
    }
    return imu;
}

  //imu重启命令
// void send_imu_restart()
// {
// if (!serial_driver_ || !serial_driver_->port()->is_open()) return;

// std::vector<uint8_t> restart_cmd = {0xAA, 0x00, 0x00, 0x0D};
// try {
//     serial_driver_->port()->send(restart_cmd);
//     RCLCPP_INFO(this->get_logger(), "Sent IMU restart command");
// } catch (const std::exception & ex) {
//     RCLCPP_ERROR(this->get_logger(), "Failed to send restart cmd: %s", ex.what());
// }

// // 只发一次就取消定时器
// restart_timer_->cancel();
// }