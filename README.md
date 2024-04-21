# app_boilerplate
Cpp cross-platform application boilerplate for embedded

### 文件树

```sh
.
├── app # App 层
│   │   # Mooncake Apps
│   ├── apps 
│   │   ├── app_template # Mooncake App 模板
│   │   └── utils
│   │       └── system
│   │           ├── inputs # 系统输入组件
│   │           └── ui # 系统 UI 组件
│   │
|   |   # 资产池
│   ├── assets
│   │   ├── fonts # 字体
│   │   ├── images # 图片
│   │   ├── localization # 本地化
│   │   └── theme # 主题(颜色)
│   │
|   |   # 硬件抽象(定义)
│   └── hal
│   │
└── platforms # 平台构建层
    ├── desktop # 桌面
    └── esp32s3 # 单片机
    ...
```

