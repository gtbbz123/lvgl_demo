#include "../Inc/font_border.h"
#include <string.h>
// create 8 font on diverse direction to simulate border

static void border_draw_cb(lv_event_t *e) {
    lv_event_code_t code = lv_event_get_code(e);

    if(code != LV_EVENT_DRAW_MAIN_BEGIN)return ;
    
    lv_obj_t *label = lv_event_get_target(e);

    border_dsc_t *dsc = lv_obj_get_user_data(label);

    if(dsc == NULL) return ;

    lv_draw_ctx_t *draw_ctx = lv_event_get_draw_ctx(e);

    const char *text = lv_label_get_text(label);

    if(text == NULL || text == "\0")
    return ;

    const lv_font_t *font = lv_obj_get_style_text_font(label, dsc->sel);
    lv_opa_t opa = lv_obj_get_style_text_opa(label, dsc->sel);

    lv_area_t label_area;
    lv_obj_get_coords(label, &label_area);

    lv_point_t text_size;
    lv_txt_get_size(&text_size, text, font, 0, 0, LV_COORD_MAX, LV_TEXT_FLAG_NONE);

    lv_area_t text_area;
    text_area.x1 = label_area.x1 + (lv_area_get_width(&label_area) - text_size.x) / 2;
    text_area.y1 = label_area.y1 + (lv_area_get_height(&label_area) - text_size.y) / 2;
    text_area.x2 = text_area.x1 + text_size.x;
    text_area.y2 = text_area.y1 + text_size.y;

    lv_draw_label_dsc_t draw_dsc;
    lv_draw_label_dsc_init(&draw_dsc);
    draw_dsc.color = dsc->color;    // 使用边框颜色
    draw_dsc.font = font;            // 使用相同字体
    draw_dsc.opa = opa;              // 使用相同透明度
    draw_dsc.flag = LV_TEXT_FLAG_NONE;

    int8_t offsets[8][2] = {
        {0, (int8_t)-dsc->width},                     // 上
        {(int8_t)dsc->width, (int8_t)-dsc->width},    // 右上
        {(int8_t)-dsc->width, (int8_t)-dsc->width},   // 左上
        {(int8_t)dsc->width, 0},                       // 右
        {(int8_t)-dsc->width, 0},                      // 左
        {0, (int8_t)dsc->width},                      // 下
        {(int8_t)dsc->width, (int8_t)dsc->width},     // 右下
        {(int8_t)-dsc->width, (int8_t)dsc->width}     // 左下
    };

    for(int i = 0; i < 8; i++){
        lv_area_t border_area = text_area;
        border_area.x1 += offsets[i][0];
        border_area.x2 += offsets[i][0];
        border_area.y1 += offsets[i][1];
        border_area.y2 += offsets[i][1];

        lv_draw_label(draw_ctx, &draw_dsc, &border_area, text, NULL);
    }

}


static void border_delete_cb(lv_event_t *e) {
    lv_obj_t *label = lv_event_get_target(e);
    border_dsc_t *dsc = lv_obj_get_user_data(label);
    
    if(dsc) {
        lv_mem_free(dsc);           // 释放内存
        lv_obj_set_user_data(label, NULL);  // 清除指针
    }
}

void lv_label_add_border(lv_obj_t * label, uint8_t width, lv_color_t color, lv_style_selector_t sel){
        if(label == NULL || width == 0) return;
    
    // 分配内存存储边框参数
    border_dsc_t *dsc = lv_mem_alloc(sizeof(border_dsc_t));
    if(dsc == NULL) {
        LV_LOG_ERROR("内存分配失败");
        return;
    }
    
    // 保存参数
    dsc->width = width;
    dsc->color = color;
    dsc->sel = sel;
    
    // 将参数指针存入标签的用户数据区
    lv_obj_set_user_data(label, dsc);
    
    // 添加绘制事件回调
    lv_obj_add_event_cb(label, border_draw_cb, LV_EVENT_DRAW_MAIN_BEGIN, NULL);
    
    // 添加删除事件回调（自动清理内存）
    lv_obj_add_event_cb(label, border_delete_cb, LV_EVENT_DELETE, NULL);
    
    // 触发一次重绘，让边框立即显示
    lv_obj_invalidate(label);

    lv_obj_move_foreground(label);
}
