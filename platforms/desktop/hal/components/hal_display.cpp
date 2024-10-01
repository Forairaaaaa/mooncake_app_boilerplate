/**
 * @file hal_display.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../hal_desktop.h"
#include "../hal_config.h"
#include <mooncake_log.h>
#include <memory>
#include <M5GFX.h>
#include "utils/LGFX_AutoDetect_sdl.hpp"

using namespace mooncake;

/**
 * @brief 派生组件
 *
 */
class DisplayM5GFXDesktop : public hal_components::DisplayM5GFXBase {
public:
    bool init() override
    {
        // 创建设备
        _display = std::make_unique<LGFX>(HAL_SCREEN_WIDTH, HAL_SCREEN_HEIGHT);
        _display->init();

        // 某些电脑好像窗口弹得慢点
        lgfx::delay(300);

        // 创建全屏画布
        _canvas = std::make_unique<LGFX_Sprite>(_display.get());
        _canvas->createSprite(HAL_SCREEN_WIDTH, HAL_SCREEN_HEIGHT);

        return true;
    }

    LGFX_Device& display() override
    {
        return *_display;
    }

    LGFX_Sprite& canvas() override
    {
        return *_canvas;
    }

    void updateCanvas() override
    {
        _canvas->pushSprite(0, 0);
    }

private:
    std::unique_ptr<LGFX_Device> _display;
    std::unique_ptr<LGFX_Sprite> _canvas;
};

void HalDesktop::_display_init()
{
    mclog::info("displat init");

    // 创建组件实例
    _components.display_m5gfx = std::make_unique<DisplayM5GFXDesktop>();
    _components.display_m5gfx->init();
}
