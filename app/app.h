/**
 * @file app.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <mooncake.h>
#include <functional>
#include "hal/hal.h"
#include "shared/shared.h"
#include "assets/assets.h"

namespace APP
{
    // 依赖注入回调
    struct SetupCallback_t
    {
        std::function<void()> sharedDataInjection = nullptr;
        std::function<void()> AssetPoolInjection = nullptr;
        std::function<void()> HalInjection = nullptr;
    };

    /**
     * @brief 初始化应用层
     *
     * @param callback
     */
    void Init(SetupCallback_t callback);

    /**
     * @brief 更新应用层
     *
     */
    void Update();

    /**
     * @brief 销毁应用层
     *
     */
    void Destroy();
} // namespace APP
