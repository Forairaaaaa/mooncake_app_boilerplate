/**
 * @file touchpad.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

namespace hal_components {

class TouchpadBase {
public:
    ~TouchpadBase() = default;

    struct TouchPoint_t {
        int x = -1;
        int y = -1;
    };

    /**
     * @brief 更新触摸屏数据
     *
     */
    virtual void update() {}

    /**
     * @brief 获取当前触点
     *
     * @return const TouchPoint_t&
     */
    virtual const TouchPoint_t& getTouchPoint()
    {
        return _tp_data;
    }

protected:
    TouchPoint_t _tp_data;
};

} // namespace hal_components
