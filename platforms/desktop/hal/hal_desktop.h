/**
 * @file hal_desktop.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <hal/hal.h>

class HalDesktop : public HAL::HalBase {
public:
    std::string type() override
    {
        return "Desktop";
    }

    void init() override
    {
        // 创建组件实例等..
        _display_init();
    }

private:
    void _display_init();
};
