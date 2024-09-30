/**
 * @file app_installer.h
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
#include <memory>
#include "app_template/app_template.h"
/* Header files locator (Don't remove) */

/**
 * @brief App 安装回调
 *
 * @param mooncake
 */
inline void on_install_apps()
{
    // 安装 App
    // mooncake::GetMooncake().installApp(std::make_unique<MyApp>());
    mooncake::GetMooncake().installApp(std::make_unique<AppTemplate>());
    /* Install app locator (Don't remove) */
}
