# Mooncake app boilerplate

Mooncake 框架工程模板，以桌面端 Cmake 工程为主导，编写应用层逻辑

使用硬件抽象层（HAL）抽象不同平台的硬件行为，应用层无需关心其具体实现

要适配某个平台时，只需要派生一个自己的 HAL 类，对接行为方法即可

重构中
