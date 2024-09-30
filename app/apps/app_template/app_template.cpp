/**
 * @file app_template.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app_template.h"
#include <mooncake.h>
#include <mooncake_log.h>

using namespace mooncake;

AppTemplate::AppTemplate()
{
    // 配置 App 信息
    setAppInfo().name = "AppTemplate";
}

void AppTemplate::onCreate()
{
    mclog::tagInfo(getAppInfo().name, "onCreate");

    // 打开自己
    open();
}

void AppTemplate::onOpen()
{
    mclog::tagInfo(getAppInfo().name, "onOpen");
}

void AppTemplate::onRunning()
{
    // mclog::tagInfo(getAppInfo().name, "onRunning");
}

void AppTemplate::onClose()
{
    mclog::tagInfo(getAppInfo().name, "onClose");
}
