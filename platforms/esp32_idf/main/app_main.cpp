/**
 * @file app_main.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <app.h>
#include <memory>
#include <hal/hal.h>
#include "hal/hal_esp32.h"

extern "C" void app_main(void)
{
    // 应用层初始化回调
    APP::InitCallback_t callback;

    callback.onHalInjection = []() {
        // 注入桌面平台的硬件抽象
        HAL::Inject(std::make_unique<HalEsp32>());
    };

    // 应用层启动
    APP::Init(callback);
    while (!APP::IsDone()) {
        APP::Update();
    }
    APP::Destroy();
}
