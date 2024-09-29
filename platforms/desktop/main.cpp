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
    APP::SetupCallback_t callback;

    // 资产池依赖注入
    callback.AssetPoolInjection = []() {};

    // HAL 依赖注入
    callback.HalInjection = []() {};

    // 共享资源池依赖注入
    callback.sharedDataInjection = []() {};

    // 启动应用层
    APP::Init(callback);
    while (1)
    {
        APP::Update();
    }
    APP::Destroy();

    return 0;
}
