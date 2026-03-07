#ifndef __FONET_BORDER_H
#define __FONET_BORDER_H
#include "../../../lvgl/lvgl.h"

typedef struct {
    uint8_t width;          // 边框宽度（像素）
    lv_color_t color;       // 边框颜色
    lv_style_selector_t sel; // 样式选择器
} border_dsc_t;

// 公开API：为标签添加边框效果
void lv_label_add_border(lv_obj_t * label, uint8_t width, lv_color_t color, lv_style_selector_t sel);

#endif

