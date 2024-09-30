/**
 * @file encoder.h
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

/**
 * @brief 编码器组件基类
 *
 */
class EncoderBase {
public:
    ~EncoderBase() = default;

    /**
     * @brief 更新编码器数据
     *
     */
    virtual void update() {}

    /**
     * @brief 获取计数值
     *
     */
    virtual void getCount() {}

    /**
     * @brief 重置计数值
     *
     */
    virtual void resetCount() {}

    /**
     * @brief 动了？
     *
     * @return true
     * @return false
     */
    virtual bool wasMoved()
    {
        return false;
    }
};

} // namespace hal_components
