# app_boilerplate
Cpp cross-platform application boilerplate for embedded

### 文件树

```sh
.
├── app                           # App 层
│   ├── apps                      # Mooncake Apps
│   │   ├── app_template          # Mooncake App 模板
│   │   └── utils
│   │       └── system            # 系统通用组件
│   │           ├── inputs        # 输入组件
│   │           └── ui            # UI 组件
│   ├── assets                    # 资产池
│   │   ├── fonts                 # 字体
│   │   ├── images                # 图片
│   │   ├── localization          # 本地化
│   │   └── theme                 # 主题(颜色)
│   └── hal                       # 硬件抽象(定义)
└── platforms                     # 平台构建层
    ├── desktop                   # 桌面
    └── esp32s3                   # 单片机
    ...
```

