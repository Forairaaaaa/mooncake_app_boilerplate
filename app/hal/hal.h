/**
 * @file hal.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <memory>
#include <string>
#include "components/components_config.h"
#include "components/system_control.h"
#include "components/imu.h"
#include "components/buzzer.h"
#include "components/touchpad.h"
#include "components/encoder.h"
#include "components/system_config.h"
#include "components/display_m5gfx.h"

/**
 * @brief 硬件抽象层
 *
 */
namespace HAL {

/**
 * @brief 硬件抽象基类
 *
 */
class HalBase {
public:
    virtual ~HalBase() = default;

    /* -------------------------------------------------------------------------- */
    /*                                Hardware APIs                               */
    /* -------------------------------------------------------------------------- */
    // 硬件行为抽象，也就是创建自己的 HAL 时所要重写的方法
    // 在这里加上你需要的虚函数方法
    // 比如从某个接口拉取信息：
    // virtual std::string fetchInfoFromHttp(std::string api) { return ""; }
    // 如果行为比较复杂的，可以封装成组件，参考 components 目录

    /**
     * @brief 获取硬件抽象类型
     *
     * @return std::string
     */
    virtual std::string type()
    {
        return "Base";
    }

    /**
     * @brief 在这里初始化硬件，以及组件的实例创建
     *
     */
    virtual void init() {}

    /* -------------------------------------------------------------------------- */
    /*                              Components Getter                             */
    /* -------------------------------------------------------------------------- */
    // 组件获取接口

#if HAL_ENABLE_COMPONENT_SYSTEM_CONTROL
    hal_components::SystemControlBase& SystemControl();
#endif

#if HAL_ENABLE_COMPONENT_IMU
    hal_components::ImuBase& Imu();
#endif

#if HAL_ENABLE_COMPONENT_BUZZER
    hal_components::BuzzerBase& Buzzer();
#endif

#if HAL_ENABLE_COMPONENT_TOUCHPAD
    hal_components::TouchpadBase& Touchpad();
#endif

#if HAL_ENABLE_COMPONENT_ENCODER
    hal_components::EncoderBase& Encoder();
#endif

#if HAL_ENABLE_COMPONENT_SYSTEM_CONFIG
    hal_components::SystemConfigBase& SystemConfig();
#endif

    hal_components::DisplayM5GFXBase& Display();

protected:
    // 组件实例管理
    struct Data_t {
#if HAL_ENABLE_COMPONENT_SYSTEM_CONTROL
        std::unique_ptr<hal_components::SystemControlBase> system_control;
#endif
#if HAL_ENABLE_COMPONENT_IMU
        std::unique_ptr<hal_components::ImuBase> imu;
#endif
#if HAL_ENABLE_COMPONENT_BUZZER
        std::unique_ptr<hal_components::BuzzerBase> buzzer;
#endif
#if HAL_ENABLE_COMPONENT_TOUCHPAD
        std::unique_ptr<hal_components::TouchpadBase> touchpad;
#endif
#if HAL_ENABLE_COMPONENT_ENCODER
        std::unique_ptr<hal_components::EncoderBase> encoder;
#endif
#if HAL_ENABLE_COMPONENT_SYSTEM_CONFIG
        std::unique_ptr<hal_components::SystemConfigBase> system_config;
#endif

        std::unique_ptr<hal_components::DisplayM5GFXBase> display_m5gfx;
    };
    Data_t _components;
};

/* -------------------------------------------------------------------------- */
/*                                  Singleton                                 */
/* -------------------------------------------------------------------------- */
// 提供一个可注入的全局单例

/**
 * @brief 获取当前 HAL 实例
 *
 * @return HalBase&
 */
HalBase& Get();

/**
 * @brief 注入 HAL，期间会调用 init() 以初始化 HAL
 *
 * @param hal
 */
void Inject(std::unique_ptr<HalBase> hal);

/**
 * @brief 销毁当前 HAL 实例
 *
 */
void Destroy();

} // namespace HAL

/**
 * @brief 获取当前 HAL 实例
 *
 * @return HAL::HalBase&
 */
inline HAL::HalBase& GetHAL()
{
    return HAL::Get();
}

/**
 * @brief 获取屏幕组件
 *
 * @return hal_components::DisplayM5GFXBase&
 */
inline hal_components::DisplayM5GFXBase& GetDisplay()
{
    return GetHAL().Display();
}
