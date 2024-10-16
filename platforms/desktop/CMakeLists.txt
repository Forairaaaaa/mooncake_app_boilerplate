cmake_minimum_required (VERSION 3.8)
project(DesktopBuild)

cmake_policy(SET CMP0077 NEW)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DPLATFORM_BUILD_DESKTOP)

# Mooncake 
set(MOONCAKE_BUILD_EXAMPLE OFF)
add_subdirectory(dependencies/mooncake)

# Mooncake log
set(MOONCAKE_EVENT_BUILD_EXAMPLE OFF)
add_subdirectory(dependencies/mooncake_log)

# Mooncake event
set(MOONCAKE_EVENT_BUILD_EXAMPLE OFF)
add_subdirectory(dependencies/mooncake_event)

# App layer
file(GLOB_RECURSE APP_LAYER_SRCS
    app/*.c
    app/*.cc
    app/*.cpp
)
set(APP_LAYER_INCS
    app/
)
add_library(app_layer ${APP_LAYER_SRCS})
target_include_directories(app_layer PUBLIC ${APP_LAYER_INCS})
target_link_libraries(app_layer PUBLIC mooncake mooncake_log mooncake_event)

# Lvgl
set(LV_CONF_INCLUDE_SIMPLE OFF)
set(LV_CONF_PATH ../../lv_conf.h)
add_subdirectory(dependencies/lvgl)
target_link_libraries(app_layer PUBLIC lvgl lvgl_examples lvgl_demos)

# SDL
find_package(SDL2 REQUIRED SDL2)
include_directories(PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(lvgl PUBLIC ${SDL2_INCLUDE_DIRS})

# 串口插件
option(ENABLE_SERIAL_DESKTOP "Enable serial desktop" OFF)
if(ENABLE_SERIAL_DESKTOP)
    add_definitions(-DENABLE_SERIAL_DESKTOP)
    # Require: https://github.com/wjwwood/serial
    find_package(serial REQUIRED)
    # target_link_libraries(app_layer PUBLIC serial)
endif()

# PNG 转 RGB565 插件
option(ENABLE_PNG_CONVERTOR "Enable png convertor" OFF)
if(ENABLE_PNG_CONVERTOR)
    add_definitions(-DENABLE_PNG_CONVERTOR)
    # libpng
    find_package(PNG REQUIRED)
    # target_link_libraries(app_layer PUBLIC ${PNG_LIBRARY})
endif()

# 桌面端源文件
file(GLOB_RECURSE APP_DESKTOP_BUILD_SRCS
    platforms/desktop/*.cpp
    platforms/desktop/*.cc
    platforms/desktop/*.c
)
add_executable(app_desktop_build ${APP_DESKTOP_BUILD_SRCS})
target_link_libraries(app_desktop_build PUBLIC app_layer ${SDL2_LIBRARIES})

# 设置构建路径
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build/desktop)

# 确保构建路径存在
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR})

# 设置生成的可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# # 设置生成的库文件输出路径
# set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
