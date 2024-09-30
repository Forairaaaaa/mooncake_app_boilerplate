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

int main()
{
    APP::InitCallback_t callback;

    // 硬件抽象层依赖注入
    callback.onHalInjection = []() {};

    // 应用层启动
    APP::Init(callback);
    while (!APP::IsDone()) {
        APP::Update();
    }
    APP::Destroy();

    return 0;
}
