/**
 * @file app.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app.h"
#include "hal/hal.h"
#include "apps/app_installer.h"
#include <memory>
#include <mooncake.h>
#include <mooncake_log.h>

using namespace mooncake;

static std::unique_ptr<Mooncake> _mooncake;
static const std::string _tag = "APP";

void APP::Init(InitCallback_t callback)
{
    mclog::tagInfo(_tag, "init");

    /* -------------------------- Asset Pool Injection -------------------------- */
    // 资产池注入
    mclog::tagInfo(_tag, "asset pool injection");
    if (callback.onAssetPoolInjection) {
        callback.onAssetPoolInjection();
    }

    /* ------------------------------ HAL Injection ----------------------------- */
    // 硬件抽象层注入
    mclog::tagInfo(_tag, "hal injection");
    if (callback.onHalInjection) {
        callback.onHalInjection();
    }

    /* -------------------------------- Mooncake -------------------------------- */
    // Mooncake 初始化
    mclog::tagInfo(_tag, "create mooncake");

    // 创建实例
    _mooncake.reset();
    _mooncake = std::make_unique<Mooncake>();
    _mooncake->logAboutMsg();

    // 安装 App
    on_install_apps(_mooncake.get());
}

void APP::Update()
{
    // 更新 Mooncake
    _mooncake->update();

    // 重置看门狗
#if HAL_ENABLE_COMPONENT_SYSTEM_CONTROL
    GetHAL()->SystemControl()->feedTheDog();
#endif
}

void APP::Destroy()
{
    _mooncake.reset();
    HAL::Destroy();
}
