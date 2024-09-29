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
#include "components/system_ctrl.h"
#include "components/imu.h"
#include "components/system_config.h"

/* -------------------------------------------------------------------------- */
/*                              Component Config                              */
/* -------------------------------------------------------------------------- */
// 组件裁剪
#define HAL_ENABLE_COMPONENT_SYSTEM_CONTROL 1
#define HAL_ENABLE_COMPONENT_IMU            1
#define HAL_ENABLE_COMPONENT_BUTTON         1
#define HAL_ENABLE_COMPONENT_TOUCHPAD       1
#define HAL_ENABLE_COMPONENT_ENCODER        1
#define HAL_ENABLE_COMPONENT_SYSTEM_CONFIG  1
#define HAL_ENABLE_COMPONENT_BUZZER         1

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
     * @brief 初始化硬件
     *
     */
    virtual void init() {}

    /* -------------------------------------------------------------------------- */
    /*                              Components Getter                             */
    /* -------------------------------------------------------------------------- */
    // 组件获取接口

#if HAL_ENABLE_COMPONENT_SYSTEM_CONTROL
    hal_components::SystemControlBase* SystemControl();
#endif

#if HAL_ENABLE_COMPONENT_IMU
    hal_components::ImuBase* Imu();
#endif

#if HAL_ENABLE_COMPONENT_SYSTEM_CONFIG
    hal_components::SystemConfigBase* SystemConfig();
#endif

protected:
    // 组件实例管理
    struct Data_t {
        std::unique_ptr<hal_components::SystemControlBase> system_control;
        std::unique_ptr<hal_components::ImuBase> imu;
        std::unique_ptr<hal_components::SystemConfigBase> system_config;
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
 * @return HAL*
 */
HalBase* Get();

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
 * @return HAL::HalBase*
 */
inline HAL::HalBase* GetHAL()
{
    return HAL::Get();
}
