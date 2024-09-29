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

    // 资产池依赖注入
    callback.onAssetPoolInjection = []() {};

    // HAL 依赖注入
    callback.onHalInjection = []() {};

    // 启动应用层
    APP::Init(callback);
    while (1) {
        APP::Update();
    }
    APP::Destroy();

    return 0;
}
