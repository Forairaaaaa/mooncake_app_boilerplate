/**
 * @file app_template.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date <date></date>
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <mooncake.h>

/**
 * @brief 派生 App
 *
 */
class AppTemplate : public mooncake::AppAbility {
public:
    AppTemplate();

    // 重写生命周期回调
    void onCreate() override;
    void onOpen() override;
    void onRunning() override;
    void onClose() override;
};
