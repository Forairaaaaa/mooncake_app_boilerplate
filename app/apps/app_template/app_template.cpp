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
#include "hal/hal.h"
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
    mclog::tagInfo(getAppInfo().name, "on create");

    // 打开自己
    open();
}

void AppTemplate::onOpen()
{
    mclog::tagInfo(getAppInfo().name, "on open");
}

int32_t target_x = 160 * 256;
int32_t target_y = 120 * 256;
int32_t current_x = 0;
int32_t current_y = 0;
int32_t add_x = 0;
int32_t add_y = 0;

void AppTemplate::onRunning()
{
    // mclog::tagInfo(getAppInfo().name, "on running");

    static int i;
    i += 6;
    GetDisplay().display().fillCircle(current_x >> 8, current_y >> 8, 5, i);
    current_x += add_x;
    current_y += add_y;
    add_x += (current_x < target_x) ? 1 : -1;
    add_y += (current_y < target_y) ? 1 : -1;
    lgfx::touch_point_t new_tp;
    if (GetDisplay().display().getTouch(&new_tp)) {
        target_x = new_tp.x * 256;
        target_y = new_tp.y * 256;
        GetDisplay().display().drawCircle(new_tp.x, new_tp.y, 5, TFT_WHITE);
    }
    lgfx::delay(1);

    GetDisplay().display().fillRect(i & 127, i >> 7, 16, 16, i);
}

void AppTemplate::onClose()
{
    mclog::tagInfo(getAppInfo().name, "on close");
}
