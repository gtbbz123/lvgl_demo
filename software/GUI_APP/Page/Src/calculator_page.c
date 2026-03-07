#include "../Inc/calculator_page.h"
#include "../../../lvgl/lvgl.h"
#include "../Inc/page_manage.h"

#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#if (USE_HW == 0)
#include <stdio.h>
#endif 

//#define DEBUG_CALCULATOR_PAGE
#ifdef DEBUG_CALCULATOR_PAGE
#define CALCULATOR_PAGE_DEBUG(x) do {printf("[%s,%d]", __FILE__, __LINE__); printf x ;}while(0)
#else 
#define CALCULATOR_PAGE_DEBUG(x)
#endif




static void calculator_page_init(void);
static void calculator_page_deinit(void);

static void event_btnmatrix_draw_cb(lv_event_t *e);
static void event_btnmatrix_pressed_cb(lv_event_t *e);
static void event_btnmatrix_release_cb(lv_event_t *e);
static double calculate(const char* str);

lv_obj_t *ui_calculator_page;
static lv_obj_t *btnmatrix;
static bool btnmatrix_is_pressed = false;
static const char *map[] =
{"+", "-", "*","/", "\n",
 "1", "2", "3", "AC", "\n",
"4", "5", "6", "0","\n",
"7", "8", "9", "=", ""};

static lv_obj_t *textarea;

Page_t calculator_page = {calculator_page_init, calculator_page_deinit, &ui_calculator_page};


static void calculator_page_init(void){
    CALCULATOR_PAGE_DEBUG(("calculator_page_init\n"));

    //page
    ui_calculator_page = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(ui_calculator_page, lv_color_hex(PAGE_COLOR), LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui_calculator_page, LV_OBJ_FLAG_SCROLLABLE);
    //textarea
    textarea = lv_textarea_create(ui_calculator_page);
    lv_obj_set_style_bg_color(textarea, lv_color_hex(PAGE_COLOR), LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(textarea, lv_color_hex(PAGE_COLOR), LV_STATE_DEFAULT);
    lv_textarea_set_text(textarea, "input");
    lv_obj_set_style_text_font(textarea, &lv_font_montserrat_44, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(textarea, lv_color_hex(0xffffff),LV_STATE_DEFAULT);
    lv_textarea_set_text_selection(textarea, true);
    //textarea_label
    lv_obj_t *textarea_label = lv_textarea_get_label(textarea);
    static lv_style_t textarea_label_style;
    lv_style_init(&textarea_label_style);
    lv_style_set_bg_color(&textarea_label_style, lv_color_hex(0x2196F3)); // 蓝色背景
    lv_style_set_text_color(&textarea_label_style, lv_color_hex(0xFFFFFF)); // 白色文字
    lv_obj_add_style(textarea_label, &textarea_label_style, LV_PART_SELECTED);
    lv_label_set_text_sel_start(textarea_label, 0);
    lv_label_set_text_sel_end(textarea_label, 5);

    //btnmatrix
    btnmatrix = lv_btnmatrix_create(ui_calculator_page);
    lv_btnmatrix_set_map(btnmatrix, map);
    lv_obj_set_size(btnmatrix, lv_obj_get_width(ui_calculator_page),200);
    lv_obj_align(btnmatrix, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(btnmatrix, lv_color_hex(PAGE_COLOR), LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(btnmatrix, lv_color_hex(PAGE_COLOR), LV_STATE_DEFAULT);

    lv_obj_add_event_cb(btnmatrix, event_btnmatrix_draw_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);
    lv_obj_add_event_cb(btnmatrix, event_btnmatrix_pressed_cb, LV_EVENT_PRESSED, NULL);
    lv_obj_add_event_cb(btnmatrix, event_btnmatrix_release_cb, LV_EVENT_RELEASED, NULL);
}
static void calculator_page_deinit(void){

}
static void event_btnmatrix_pressed_cb(lv_event_t *e){
    static bool is_first = 1;
    btnmatrix_is_pressed = 1;
    char str[32];
    if(is_first == 1){
        lv_textarea_set_text(textarea, "");
        is_first = 0;
    }
    uint8_t id = lv_btnmatrix_get_selected_btn(btnmatrix);
    switch(id){
        case BTN_AC:
            lv_textarea_set_text(textarea, "");
            break;
        case BTN_EQUAL:
            sprintf(str,"%.2f",calculate(lv_textarea_get_text(textarea)));
            lv_textarea_set_text(textarea, str);
            break;
        default:
            strcpy(str,lv_btnmatrix_get_btn_text(btnmatrix, id));
            lv_textarea_add_text(textarea, str);
    }
}
static void event_btnmatrix_release_cb(lv_event_t *e){
    btnmatrix_is_pressed = 0;

}
static void event_btnmatrix_draw_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_draw_part_dsc_t *dsc = (lv_obj_draw_part_dsc_t *)lv_event_get_param(e);

    if(code != LV_EVENT_DRAW_PART_BEGIN) return ;

    if(dsc->class_p != &lv_btnmatrix_class || dsc->type != LV_BTNMATRIX_DRAW_PART_BTN) return ;

    uint32_t id = dsc->id;
    dsc->radius = 8;
    switch(id){
        case BTN_ADD:
        case BTN_SUB:
        case BTN_MUL:
        case BTN_DIV:
        case BTN_AC:
            dsc->label_dsc->color = lv_color_hex(0xff7f00);
            dsc->label_dsc->font = &lv_font_montserrat_16;
            dsc->rect_dsc->bg_color = lv_color_hex(0xeeeeee);
            break;
        case BTN_EQUAL:
            dsc->label_dsc->color = lv_color_hex(0xffffff);
            dsc->rect_dsc->bg_color = lv_color_hex(0xff7f00);
            break;
        default:
            dsc->label_dsc->color = lv_color_hex(0x000000);
            dsc->rect_dsc->bg_color = lv_color_hex(0xeeeeee);
    }
    if(btnmatrix_is_pressed && id == lv_btnmatrix_get_selected_btn(btnmatrix)){
        dsc->rect_dsc->bg_color = lv_color_darken(dsc->rect_dsc->bg_color, 50);
    }
}


static double calculate(const char* str){
    double result = 0.0;
    double num;
    char op = '+';
    const char* p = str;
    
    // 跳过开头的空格
    while (*p == ' ') p++;
    
    while (*p != '\0') {
        // 解析数字
        if (isdigit(*p) || *p == '.') {
            char* endptr;
            num = strtod(p, &endptr);
            p = endptr;
            
            // 根据前一个操作符进行运算
            if (op == '+') {
                result += num;
            } else if (op == '-') {
                result -= num;
            } else if (op == '*') {
                result *= num;
            } else if (op == '/') {
                if (num == 0) {
                    return NAN;  // 除以0返回NaN
                }
                result /= num;
            }
        }
        // 解析操作符
        else if (*p == '+' || *p == '-' || *p == '*' || *p == '/') {
            op = *p;
            p++;
        }
        // 跳过空格
        else if (*p == ' ') {
            p++;
        }
        // 无效字符
        else {
            return NAN;  // 返回NaN表示无效输入
        }
    }
    
    return result;
}


