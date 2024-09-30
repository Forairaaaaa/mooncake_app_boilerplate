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
#include "../hal_desktop.h"
#include "../hal_config.h"
#include <mooncake_log.h>
#include <lvgl.h>
#include <src/misc/lv_timer.h>
// // https://github.com/lvgl/lv_port_pc_vscode/blob/master/main/src/main.c

using namespace mooncake;

void HalDesktop::lvgl_init()
{
    mclog::info("lvgl init");

    lv_init();

    lv_group_set_default(lv_group_create());

    auto display = lv_sdl_window_create(HAL_SCREEN_WIDTH, HAL_SCREEN_HEIGHT);
    lv_display_set_default(display);

    auto mouse = lv_sdl_mouse_create();
    lv_indev_set_group(mouse, lv_group_get_default());
    lv_indev_set_display(mouse, display);

    // LV_IMAGE_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
    // lv_obj_t* cursor_obj;
    // cursor_obj = lv_image_create(lv_screen_active()); /*Create an image object for the cursor */
    // lv_image_set_src(cursor_obj, &mouse_cursor_icon); /*Set the image source*/
    // lv_indev_set_cursor(mouse, cursor_obj);           /*Connect the image  object to the driver*/

    auto mouse_wheel = lv_sdl_mousewheel_create();
    lv_indev_set_display(mouse_wheel, display);
    lv_indev_set_group(mouse_wheel, lv_group_get_default());

    auto keyboard = lv_sdl_keyboard_create();
    lv_indev_set_display(keyboard, display);
    lv_indev_set_group(keyboard, lv_group_get_default());
}
