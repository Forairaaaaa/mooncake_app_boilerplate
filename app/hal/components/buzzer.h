/**
 * @file buzzer.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <cstdint>
#include <string>

namespace hal_components {

/**
 * @brief 蜂鸣器组件基类
 *
 */
class BuzzerBase {
public:
    ~BuzzerBase() = default;

    /**
     * @brief 开始哔哔
     *
     * @param frequency
     * @param duration
     */
    virtual void beep(float frequency, std::uint32_t duration = 0xFFFFFFFF) {}

    /**
     * @brief 是否在叫
     *
     * @return true
     * @return false
     */
    virtual bool isBeeping()
    {
        return false;
    }

    /**
     * @brief 别叫了
     *
     */
    virtual void stop() {}

    /**
     * @brief 播放 RTTTL 音乐
     *
     * @param rtttlMusic
     */
    virtual void playRtttlMusic(const std::string& rtttlMusic) {}
    // RTTTL 格式参考：
    // https://en.wikipedia.org/wiki/Ring_Tone_Text_Transfer_Language
    // https://adamonsoon.github.io/rtttl-play/
    // https://picaxe.com/rtttl-ringtones-for-tune-command/
};

} // namespace hal_components
