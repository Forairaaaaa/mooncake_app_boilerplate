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
#include "hal/components/imu.h"
#include "hal/components/system_ctrl.h"
#include <memory>
#include <mooncake_log.h>

using namespace mooncake;

/* -------------------------------------------------------------------------- */
/*                                  Singleton                                 */
/* -------------------------------------------------------------------------- */
// 提供一个可注入的全局单例

static std::unique_ptr<HAL::HalBase> _hal_instance;
static const std::string _tag = "HAL";

HAL::HalBase* HAL::Get()
{
    if (!_hal_instance) {
        mclog::tagWarn(_tag, "getting null hal, auto inject base");
        _hal_instance = std::make_unique<HalBase>();
    }
    return _hal_instance.get();
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

    // 初始化
    mclog::tagInfo(_tag, "init injected hal");
    _hal_instance->init();
    mclog::tagInfo(_tag, "done");
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
hal_components::SystemControlBase* HAL::HalBase::SystemControl()
{
    if (!_components.system_control) {
        mclog::tagWarn(_tag, "getting null system config component");
        _components.system_control = std::make_unique<hal_components::SystemControlBase>();
    }
    return _components.system_control.get();
}
#endif

#if HAL_ENABLE_COMPONENT_IMU
hal_components::ImuBase* HAL::HalBase::Imu()
{
    if (!_components.imu) {
        mclog::tagWarn(_tag, "getting null imu component");
        _components.imu = std::make_unique<hal_components::ImuBase>();
    }
    return _components.imu.get();
}
#endif

#if HAL_ENABLE_COMPONENT_SYSTEM_CONFIG
hal_components::SystemConfigBase* HAL::HalBase::SystemConfig()
{
    if (!_components.system_config) {
        mclog::tagWarn(_tag, "getting null system config component");
        _components.system_config = std::make_unique<hal_components::SystemConfigBase>();
    }
    return _components.system_config.get();
}
#endif
