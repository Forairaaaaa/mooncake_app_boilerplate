/**
 * @file app.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <mooncake.h>
#include <functional>

/**
 * @brief 应用层
 *
 */
namespace APP {

// 依赖注入回调
struct InitCallback_t {
    std::function<void()> onAssetPoolInjection = nullptr;
    std::function<void()> onHalInjection = nullptr;
};

/**
 * @brief 初始化应用层
 *
 * @param callback
 */
void Init(InitCallback_t callback);

/**
 * @brief 更新应用层
 *
 */
void Update();

/**
 * @brief 结束力
 *
 * @return true
 * @return false
 */
bool IsDone();

/**
 * @brief 销毁应用层
 *
 */
void Destroy();

} // namespace APP
