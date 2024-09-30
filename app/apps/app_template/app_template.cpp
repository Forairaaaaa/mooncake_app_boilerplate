/**
 * @file app_template.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date <date></date>
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "app_template.h"
#include <mooncake.h>
#include <mooncake_log.h>
#include <lvgl.h>
#include <lv_demos.h>
#include <widgets/lv_example_widgets.h>

using namespace mooncake;

AppTemplate::AppTemplate()
{
    // 配置 App 信息
    setAppInfo().name = "AppTemplate";
}

void AppTemplate::onCreate()
{
    mclog::tagInfo(getAppInfo().name, "on create");

    // 打开自己
    open();
}

void AppTemplate::onOpen()
{
    mclog::tagInfo(getAppInfo().name, "on open");

    lv_demo_widgets();
    // lv_example_button_1();
}

void AppTemplate::onRunning()
{
    // mclog::tagInfo(getAppInfo().name, "on running");

    lv_timer_handler();
}

void AppTemplate::onClose()
{
    mclog::tagInfo(getAppInfo().name, "on close");
}
