/**
 * @file main.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <Arduino.h>
#include <mooncake.h>
#include <memory>
// #include <app.h>
// #include <memory>
// #include <hal/hal.h>
// #include "hal/hal_esp32.h"

using namespace mooncake;

void setup()
{
    // // 应用层初始化回调
    // APP::InitCallback_t callback;

    // callback.onHalInjection = []() {
    //     // 注入桌面平台的硬件抽象
    //     // HAL::Inject(std::make_unique<HalEsp32>());
    // };

    // // 应用层启动
    // APP::Init(callback);

    auto shit = std::make_shared<Mooncake>();
    auto shit = std::make_unique<Mooncake>();
}

void loop()
{
    // APP::Update();
}
