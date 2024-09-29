/**
 * @file system_ctrl.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <cstdint>

namespace hal_components {

/**
 * @brief 系统操作组件基类，提供系统杂项控制接口
 *
 */
class SystemControlBase {
public:
    ~SystemControlBase() = default;

    /**
     * @brief 延时
     *
     * @param ms
     */
    virtual void delay(std::uint32_t ms) {}

    /**
     * @brief 获取当前系统运行毫秒数
     *
     * @return std::uint32_t
     */
    virtual std::uint32_t millis()
    {
        return 0;
    }

    /**
     * @brief 重启
     *
     */
    virtual void reboot() {}

    /**
     * @brief 关机
     *
     */
    virtual void powerOff() {}

    /**
     * @brief 重置系统看门狗
     *
     */
    virtual void feedTheDog() {}
};

} // namespace hal_components
