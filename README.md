# Mooncake app boilerplate

适用于嵌入式应用的跨平台 App 样板

框架主要目的：在桌面端编写应用层（UI逻辑、算法验证等），并方便同步到嵌入式端（平台解耦）

主要构成：

### Mooncake App 模板

Mooncake App [模板](https://github.com/Forairaaaaa/mooncake_app_boilerplate/tree/main/app/apps/app_template)，以及 App [快速创建脚本](https://github.com/Forairaaaaa/mooncake_app_boilerplate/blob/main/app/apps/app_generator.py)，App [注入接口封装](https://github.com/Forairaaaaa/mooncake_app_boilerplate/blob/main/app/apps/apps.h)

### HAL 硬件抽象层

[HAL](https://github.com/Forairaaaaa/mooncake_app_boilerplate/blob/main/app/hal/hal.h#L26) 硬件抽象层（单例+依赖注入），用于架空应用层

不同的硬件只需要按需[派生](https://github.com/Forairaaaaa/mooncake_app_boilerplate/blob/main/platforms/esp32s3/main/hal_esp32s3/hal_esp32s3.h#L13)出自己的HAL，并在初始化时[注入](https://github.com/Forairaaaaa/mooncake_app_boilerplate/blob/main/platforms/esp32s3/main/app_main.cpp#L52)即可

可以减少应用移植成本，方便调试，比如直接在[桌面端](https://github.com/Forairaaaaa/mooncake_app_boilerplate/blob/main/platforms/desktop/hal_desktop/hal_desktop.hpp#L21)写好应用层，再适配单片机HAL即可，无需反复编译上传固件，慢的一

### AssetPool 资产池抽象

[AssetPool](https://github.com/Forairaaaaa/mooncake_app_boilerplate/blob/main/platforms/desktop/hal_desktop/hal_desktop.hpp#L21) 资产池抽象（单例+依赖注入），用于管理字体、图片、网页、多语言文本池等静态资源

目的是将静态资源结构体化、可序列化：可以在桌面端把资产池[序列化](https://github.com/Forairaaaaa/mooncake_app_boilerplate/blob/main/platforms/desktop/main.cpp#L22)为 bin 文件，序列化后的 bin 文件可以被[写入](https://github.com/Forairaaaaa/mooncake_app_boilerplate/blob/main/platforms/esp32s3/upload_asset_pool.sh) 到 esp32 的特定分区，然后在 esp32 初始化时，将该分区的映射地址[注入](https://github.com/Forairaaaaa/mooncake_app_boilerplate/blob/main/platforms/esp32s3/main/app_main.cpp#L27)到资产池，可以减少app分区体积，加快调试上传速度

因为静态资源是[定义](https://github.com/Forairaaaaa/Regina/blob/main/app/assets/images/types.h#L29)在结构体里的，并且指定了内存大小，所以应用层在[调用静态资源](https://github.com/Forairaaaaa/Regina/blob/main/app/apps/app_startup_anim/app_startup_anim.cpp#L52)时，无需再关心该资源的内存地址偏移，编译器会自己算好

此外还有一些常用的，桌面端上复制静态资源的 api，如[读取任意文件并写入内存](https://github.com/Forairaaaaa/mooncake_app_boilerplate/blob/main/app/assets/assets.cpp#L113)、[读取 PNG 图片转换为 RGB565 并写入内存](https://github.com/Forairaaaaa/mooncake_app_boilerplate/blob/main/app/assets/assets.cpp#L143)

### SharedData 共享数据抽象

[SharedData](https://github.com/Forairaaaaa/mooncake_app_boilerplate/blob/main/app/shared/shared.h#L21) 共享数据抽象（单例+依赖注入），提供一个全局共享的数据池，可用于不同 Mooncake App 间、或者 App 和 HAL 间的数据共享

在初始化时，同样可以由注入不同的[派生](https://github.com/Forairaaaaa/mooncake_app_boilerplate/blob/main/app/shared/shared.h#L88)来实现不同的数据锁，比如桌面端的 std::mutex，单片机端的 freertos mutex

## 文件树

```sh
.
├── app                           # [App 层]
│   ├── apps                        # [Mooncake Apps层]
│   │   ├── app_template              # Mooncake App 模板
│   │   └── utils
│   │       └── system                # 系统通用组件
│   │           ├── inputs              # 输入组件
│   │           └── ui                  # UI 组件
│   ├── assets                      # 资产池抽象
│   │   ├── fonts                     # 字体
│   │   ├── images                    # 图片
│   │   ├── localization              # 本地化
│   │   └── theme                     # 主题(颜色)
│   ├── hal                         # 硬件层抽象
|   └── shared                      # 全局共享数据抽象
└── platforms                     # [平台构建层]
    ├── desktop                     # 桌面
    └── esp32s3                     # 单片机
    ...
```

## 编译

### 下载依赖

```bash
python ./fetch_repos.py
```

### 桌面端

#### 工具链

```bash
sudo apt install build-essential cmake
```

#### 编译

```bash
mkdir build && cd build
```
```bash
cmake .. && make
```
#### 运行

```bash
cd desktop
```

要先 cd 过去，因为序列化时用的相对路径 :(

```bash
./app_desktop_build
```
