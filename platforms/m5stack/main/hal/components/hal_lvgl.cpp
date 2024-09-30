/**
 * @file hal_lvgl.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-09-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "../hal_esp32.h"
#include <mooncake_log.h>
#include <lvgl.h>
#include <M5Unified.h>
// https://github.com/m5stack/lv_m5_emulator/blob/main/src/utility/lvgl_port_m5stack.cpp

using namespace mooncake;

#define LV_BUFFER_LINE 120

static void lvgl_flush_cb(lv_display_t* disp, const lv_area_t* area, uint8_t* px_map)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    M5.Display.startWrite();
    M5.Display.setAddrWindow(area->x1, area->y1, w, h);
    M5.Display.writePixels((lgfx::rgb565_t*)px_map, w * h);
    M5.Display.endWrite();

    lv_display_flush_ready(disp);
}

static void lvgl_read_cb(lv_indev_t* indev, lv_indev_data_t* data)
{
    uint16_t touchX, touchY;

    bool touched = M5.Display.getTouch(&touchX, &touchY);
    if (!touched) {
        data->state = LV_INDEV_STATE_REL;
    } else {
        data->state = LV_INDEV_STATE_PR;
        data->point.x = touchX;
        data->point.y = touchY;
    }
}

static void lvgl_tick_timer(void* arg)
{
    (void)arg;
    lv_tick_inc(10);
}

void HalEsp32::lvgl_init()
{
    mclog::info("lvgl init");

    M5.begin();

    lv_init();

    // Display
    auto display = lv_display_create(M5.Display.width(), M5.Display.height());
    lv_display_set_flush_cb(display, lvgl_flush_cb);

    static uint8_t* buf1 = (uint8_t*)malloc(M5.Display.width() * LV_BUFFER_LINE);
    lv_display_set_buffers(display, (void*)buf1, NULL, M5.Display.width() * LV_BUFFER_LINE,
                           LV_DISPLAY_RENDER_MODE_PARTIAL);

    // Touch
    static lv_indev_t* indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, lvgl_read_cb);
    lv_indev_set_display(indev, display);

    // Tick
    const esp_timer_create_args_t periodic_timer_args = {.callback = &lvgl_tick_timer, .name = "lvgl_tick_timer"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 10 * 1000));
}
