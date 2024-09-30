/**
 * @file assets.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <string>
#include <cstdint>

/**
 * @brief 资产层，方便 App 的静态资源访问
 *
 */
namespace Asset {

/**
 * @brief 资产池定义，静态资源都可以放在这里
 *
 */
struct AssetPool_t {
    // 比如文本：
    std::string text_hello = "我上早八";
    // 颜色
    std::uint32_t color_text_hello = 0x114514;
    // 图片
    std::uint16_t* image_icon_hello = nullptr;
};

/**
 * @brief 资产池初始化回调，可以在这里面赋值你的图片指针等
 *
 * @param assetPool
 */
void on_asset_pool_init(AssetPool_t& assetPool);

/* -------------------------------------------------------------------------- */
/*                                  Singleton                                 */
/* -------------------------------------------------------------------------- */
// 全局单例

/**
 * @brief 获取资产池
 *
 * @return AssetPool_t&
 */
AssetPool_t& Get();

/**
 * @brief 销毁当前 HAL 实例
 *
 */
void Destroy();

/**
 * @brief 资产池注入，因为很多单片机都可以将 flash
 * 的某块分区映射到内存上进行访问，就是说可以将静态资源和 app 分区分隔开。
 * 当然直接走文件系统要优雅很多，这个只适用于希望 app 分区尽量小、又对资源访问速度有需求的情况。
 * 所以这里暴露一个注入接口，单片机可以将映射的地址注入进来
 *
 * @param assetPool
 */
void Inject(AssetPool_t* assetPool);

// 以 ESP32 举例，我可以这样定义资产池
// struct AssetPool_t {
//     uint16_t image_hello[114514];
//     uint16_t image_bye[1919810];
// };

// 在桌面端的资产池注入回调时，构造一个 AssetPool_t 实例，把图片的数据复制到 image_hello 和 image_bye 里面
// 然后将这个结构体序列化成一个 bin 文件

// 这个 bin 文件可以写入到 ESP32 里的某个分区，在启动时调用 api 映射到内存上
// 到这里 ESP32 就相当于有了一个 AssetPool_t 实例了
// 注入到资产层以后，Get()->image_bye 就可以访问这个图片的数据了

} // namespace Asset

inline Asset::AssetPool_t& GetAsset()
{
    return Asset::Get();
}
