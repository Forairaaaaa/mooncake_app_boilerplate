/**
 * @file hal.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "hal.h"
#include "hal/components/display_m5gfx.h"
#include <memory>
#include <string>
#include <mooncake_log.h>

using namespace mooncake;

/* -------------------------------------------------------------------------- */
/*                                  Singleton                                 */
/* -------------------------------------------------------------------------- */
// 提供一个可注入的全局单例

static std::unique_ptr<HAL::HalBase> _hal_instance;
static const std::string _tag = "HAL";

HAL::HalBase& HAL::Get()
{
    if (!_hal_instance) {
        mclog::tagWarn(_tag, "getting null hal, auto inject base");
        _hal_instance = std::make_unique<HalBase>();
    }
    return *_hal_instance.get();
}

void HAL::Inject(std::unique_ptr<HalBase> hal)
{
    if (!hal) {
        mclog::tagError(_tag, "pass null hal");
        return;
    }

    // 销毁已有实例，储存新实例
    Destroy();
    _hal_instance = std::move(hal);

    // 看看何方神圣
    mclog::tagInfo(_tag, "injecting hal type: {}", _hal_instance->type());

    // 初始化
    mclog::tagInfo(_tag, "invoke init");
    _hal_instance->init();
    mclog::tagInfo(_tag, "hal injected");
}

void HAL::Destroy()
{
    _hal_instance.reset();
}

/* -------------------------------------------------------------------------- */
/*                              Components Getter                             */
/* -------------------------------------------------------------------------- */
// 组件获取接口，如果当前没有实例，则懒加载一个基类，这样就算某个平台没有适配某个组件，也不会崩溃

#if HAL_ENABLE_COMPONENT_SYSTEM_CONTROL
hal_components::SystemControlBase& HAL::HalBase::SystemControl()
{
    if (!_components.system_control) {
        mclog::tagWarn(_tag, "getting null system config component");
        _components.system_control = std::make_unique<hal_components::SystemControlBase>();
    }
    return *_components.system_control.get();
}
#endif

#if HAL_ENABLE_COMPONENT_IMU
hal_components::ImuBase& HAL::HalBase::Imu()
{
    if (!_components.imu) {
        mclog::tagWarn(_tag, "getting null imu component");
        _components.imu = std::make_unique<hal_components::ImuBase>();
    }
    return *_components.imu.get();
}
#endif

#if HAL_ENABLE_COMPONENT_SYSTEM_CONFIG
hal_components::SystemConfigBase& HAL::HalBase::SystemConfig()
{
    if (!_components.system_config) {
        mclog::tagWarn(_tag, "getting null system config component");
        _components.system_config = std::make_unique<hal_components::SystemConfigBase>();
    }
    return *_components.system_config.get();
}
#endif

#if HAL_ENABLE_COMPONENT_BUZZER
hal_components::BuzzerBase& HAL::HalBase::Buzzer()
{
    if (!_components.buzzer) {
        mclog::tagWarn(_tag, "getting null buzzer component");
        _components.buzzer = std::make_unique<hal_components::BuzzerBase>();
    }
    return *_components.buzzer.get();
}
#endif

#if HAL_ENABLE_COMPONENT_TOUCHPAD
hal_components::TouchpadBase& HAL::HalBase::Touchpad()
{
    if (!_components.touchpad) {
        mclog::tagWarn(_tag, "getting null touchpad component");
        _components.touchpad = std::make_unique<hal_components::TouchpadBase>();
    }
    return *_components.touchpad.get();
}
#endif

#if HAL_ENABLE_COMPONENT_ENCODER
hal_components::EncoderBase& HAL::HalBase::Encoder()
{
    if (!_components.encoder) {
        mclog::tagWarn(_tag, "getting null encoder component");
        _components.encoder = std::make_unique<hal_components::EncoderBase>();
    }
    return *_components.encoder.get();
}
#endif

hal_components::DisplayM5GFXBase& HAL::HalBase::Display()
{
    if (!_components.display_m5gfx) {
        mclog::tagWarn(_tag, "getting null display component");
        _components.display_m5gfx = std::make_unique<hal_components::DisplayM5GFXBase>();
    }
    return *_components.display_m5gfx.get();
}
