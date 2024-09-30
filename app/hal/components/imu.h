/**
 * @file imu.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

namespace hal_components {

/**
 * @brief IMU 组件基类
 *
 */
class ImuBase {
public:
    /**
     * @brief IMU 数据
     *
     */
    struct ImuData_t {
        float accelX = 0.0;
        float accelY = 0.0;
        float accelZ = 0.0;
        float gyroX = 0.0;
        float gyroY = 0.0;
        float gyroZ = 0.0;
        float magX = 0.0;
        float magY = 0.0;
        float magZ = 0.0;
    };

    ~ImuBase() = default;

    /**
     * @brief 更新 IMU 数据
     *
     */
    virtual void update() {}

    /**
     * @brief 获取 IMU 数据
     *
     * @return const ImuData_t&
     */
    const ImuData_t& getData()
    {
        return _imu_data;
    }

protected:
    ImuData_t _imu_data;
};

} // namespace hal_components
