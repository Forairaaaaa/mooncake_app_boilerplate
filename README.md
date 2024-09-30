# Mooncake app boilerplate

Mooncake 框架工程模板，以桌面端 Cmake 工程为主导，编写应用层逻辑

使用硬件抽象层（HAL）抽象不同平台的硬件行为，应用层无需关心其具体实现

要适配某个平台时，只需要派生一个自己的 HAL 类，对接行为方法即可

重构中

### Install SDL and build tools

You can download SDL from https://www.libsdl.org/

#### Linux

Copy below in the Terminal:
For Ubuntu

```bash
sudo apt-get update && sudo apt-get install -y build-essential libsdl2-dev cmake
```

For ArchLinux

```bash
sudo pacman -Syu && sudo pacman -S sdl2 libsdl2-devel sdl2_mixer sdl2-devel base-devel gcc make
```
