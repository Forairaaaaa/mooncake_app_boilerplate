/**
 * @file m5gfx.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-10-01
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <M5GFX.h>
#include <mooncake_log.h>

namespace hal_components {

class DisplayM5GFXBase {
public:
    ~DisplayM5GFXBase() = default;

    virtual bool init()
    {
        return false;
    }

    virtual LGFX_Device& display()
    {
        mooncake::mclog::error("getting display from base");
        static auto dumb_instance = new LGFX_Device;
        return *dumb_instance;
    }

    virtual LGFX_Sprite& canvas()
    {
        mooncake::mclog::error("getting canvas from base");
        static auto dumb_instance = new LGFX_Sprite;
        return *dumb_instance;
    }

    virtual void updateCanvas() {}
};

} // namespace hal_components
