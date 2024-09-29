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
#include <cstdint>
#include <memory>
#include <string>
#include "components/system_config.h"

/**
 * @brief 硬件抽象层
 *
 */
class HAL {
public:
    virtual ~HAL() = default;

    /**
     * @brief HAL 类型
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
    /*                                Hardware APIs                               */
    /* -------------------------------------------------------------------------- */
    // 硬件行为抽象，也就是创建自己的 HAL 时所要重写的方法
    // 在这里加上你需要的虚函数方法
    // 比如从某个接口拉取信息：
    // virtual std::string fetchInfoFromHttp(std::string api) { return ""; }
    // 如果行为比较复杂的，可以封装成对象，参考 components 目录

    /* -------------------------------------------------------------------------- */
    /*                              Components Getter                             */
    /* -------------------------------------------------------------------------- */
    // 组件获取接口

    std::shared_ptr<hal_components::SystemConfigBase> SystemConfig()
    {
        return _data.system_config;
    }

protected:
    // 这里可以放一些共用的内部数据
    struct Data_t {
        std::shared_ptr<hal_components::SystemConfigBase> system_config;
    };
    Data_t _data;

public:
    /* -------------------------------------------------------------------------- */
    /*                                  Singleton                                 */
    /* -------------------------------------------------------------------------- */
    // 提供一个可注入的全局单例

    /**
     * @brief 获取当前 HAL 实例
     *
     * @return HAL*
     */
    static HAL* Get();

    /**
     * @brief 注入 HAL，期间会调用 init() 以初始化 HAL
     *
     * @param hal
     * @return true
     * @return false
     */
    static bool Inject(std::unique_ptr<HAL> hal);

    /**
     * @brief 销毁当前 HAL 实例
     *
     */
    static void Destroy();
};
