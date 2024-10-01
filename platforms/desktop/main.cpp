/**
 * @file main.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <app.h>
#include <memory>
#include <hal/hal.h>
#include "hal/hal_desktop.h"

void setup()
{
    // 应用层初始化回调
    APP::InitCallback_t callback;

    callback.onHalInjection = []() {
        // 注入桌面平台的硬件抽象
        HAL::Inject(std::make_unique<HalDesktop>());
    };

    // 应用层启动
    APP::Init(callback);
}

void loop()
{
    APP::Update();
}
