#include "../Inc/menu_page.h"
#include "../Inc/calculator_page.h"
#include "../Inc/file_manager_page.h"
#include "../Inc/calendar_page.h"
#include "../Inc/card_page.h"
#include "../Inc/device_info_page.h"
#include "../Inc/file_manager_page.h"
#include "../Inc/game_page.h"
#include "../Inc/home_page.h"
#include "../Inc/music_page.h"
#include "../Inc/picture_page.h"
#include "../Inc/settings_page.h"
#include "../Inc/stop_watch_page.h"
#include "../Inc/txt_read_page.h"
#if (USE_HW == 0)
#include <stdio.h>
#endif 

//#define DEBUG_MENU_PAGE
#ifdef DEBUG_MENU_PAGE
#define MENU_PAGE_DEBUG(x) do {printf("[%s,%d]", __FILE__, __LINE__); printf x ;}while(0)
#else 
#define MENU_PAGE_DEBUG(x)
#endif

#define PANEL_HEIGHT 50
#define PNAEL_COLOR 0x000000
#define PNAEL_PRESSED_COLOR 0x808080

#define ANIM_DELAY 500
#define ANIM_TIME 500


/***************************************************************************
因为重复性工作太多所以本文件大部分用X macro编写 效果如下
//函数声明
static void calculator_anim_cb(lv_anim_t *anim, int32_t value);
static void event_calculator_panel_cb(lv_event_t *e);
//变量定义
static lv_obj_t *calculator_panel;
static lv_obj_t *calculator_icon;
static lv_obj_t *calculator_label;
//对象的一些配置
    calculator_panel = lv_obj_create(ui_menu_page);
    lv_obj_clear_flag(calculator_panel, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(calculator_panel, lv_obj_get_width(ui_menu_page), PANEL_HEIGHT);
    lv_obj_align(calculator_panel, LV_ALIGN_TOP_MID, disp_width, 0 * PANEL_HEIGHT);//hide first then play anim
    lv_obj_set_style_bg_color(calculator_panel, lv_color_hex(PNAEL_COLOR), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(calculator_panel, lv_color_hex(PNAEL_PRESSED_COLOR), LV_STATE_PRESSED);
    lv_obj_set_style_border_color(calculator_panel, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_obj_set_style_radius(calculator_panel, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(calculator_panel, LV_BORDER_SIDE_BOTTOM, LV_STATE_DEFAULT);
    
    calculator_icon = lv_label_create(calculator_panel);
    lv_obj_align(calculator_icon, LV_ALIGN_LEFT_MID, 20, 0);
    lv_obj_set_style_text_color(calculator_icon, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_label_set_text(calculator_icon, LV_SYMBOL_SD_CARD);
    
    calculator_label = lv_label_create(calculator_panel);
    lv_obj_align_to(calculator_label, calculator_icon, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
    lv_obj_set_style_text_color(calculator_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_label_set_text(calculator_label, "CALCULATOR");
//动画注册   
    lv_anim_t calculator_anim;
    lv_anim_init(&calculator_anim);
    lv_anim_set_custom_exec_cb(&calculator_anim,calculator_anim_cb);
    lv_anim_set_values(&calculator_anim, 0, 100);
    lv_anim_set_time(&calculator_anim, ANIM_TIME);

    lv_anim_set_delay(&calculator_anim, ANIM_DELAY);
    lv_anim_start(&calculator_anim);
//事件回调
static void event_calculator_panel_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_CLICKED){
        PAGE_MANAGE_page_load(calculator_page);
    }
}
//动画回调
static void calculator_anim_cb(lv_anim_t *anim, int32_t value){
    int32_t page_width = lv_disp_get_hor_res(NULL);
    lv_obj_t *obj = anim->var;
    lv_obj_set_x(calculator_panel, page_width - page_width *(value / 100.0));
    lv_obj_set_style_opa(calculator_panel, 255 * (value/ 100.0), LV_STATE_DEFAULT);
}
****************************************************************************/

//macro register table
#define PANEL_LIST \
            X(file_manager, 1, -1, LV_SYMBOL_FILE)\
						X(calculator, 0, 1, LV_SYMBOL_PLAY)\
            X(txt_read, 2, 1, LV_SYMBOL_WARNING)\
            X(stop_watch, 3, -1, LV_SYMBOL_CALL)\
            X(music, 4, 1, LV_SYMBOL_AUDIO)\
            X(calendar, 5, -1, LV_SYMBOL_TRASH)\
            X(game, 6, 1, LV_SYMBOL_EJECT)\
            X(picture,7 ,-1, LV_SYMBOL_EJECT)\
            X(card, 8, 1, LV_SYMBOL_EJECT)\
            X(settings, 9, -1, LV_SYMBOL_EJECT)\
            X(device_info, 10, 1, LV_SYMBOL_EJECT)

//declare var
#define X(name, id, dir, symbol) \
        static lv_obj_t *name##_panel;\
        static lv_obj_t *name##_icon;\
        static lv_obj_t *name##_label;\
        static void event_##name##_panel_cb(lv_event_t *e);
				//static void name##_anim_cb(lv_anim_t *anim, int32_t value);
PANEL_LIST
#undef X

//page recall function
#define X(name, id, dir, symbol)                                      \
        static void event_##name##_panel_cb(lv_event_t *e) {      \
            lv_event_code_t code = lv_event_get_code(e);    \
            if (code == LV_EVENT_CLICKED) {                 \
                PAGE_MANAGE_page_load(&name##_page);       \
            }                                               \
        }
PANEL_LIST
#undef X
//anim recall
#define X(name, id, dir, symbol)                                                                     \
static void name##_anim_cb(lv_anim_t *anim, int32_t value){                         \
    int32_t page_width = lv_disp_get_hor_res(NULL);                                 \
    lv_obj_t *obj = anim->var;                                                      \
    lv_obj_set_x(name##_panel, (dir) *(page_width - page_width *(value / 100.0)));           \
    lv_obj_set_style_opa(name##_panel, 255 * (value/ 100.0), LV_STATE_DEFAULT);     \
}
//PANEL_LIST
#undef X

static void menu_page_init(void);
static void menu_page_deinit(void);

lv_obj_t *ui_menu_page;

Page_t menu_page = {menu_page_init, menu_page_deinit, &ui_menu_page};


static void menu_page_init(void){
    uint32_t disp_width = lv_disp_get_hor_res(NULL);

    ui_menu_page = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(ui_menu_page, lv_color_hex(PAGE_COLOR), LV_STATE_DEFAULT);
    lv_obj_set_scroll_dir(ui_menu_page, LV_DIR_VER);

    lv_obj_set_scrollbar_mode(ui_menu_page, LV_SCROLLBAR_MODE_OFF);


////////////////////////////////////////////////////////////////////////////////////////////
    #define X(name, id, dir, symbol)             \
    /*name##_panel*/\
    do{\
    name##_panel = lv_obj_create(ui_menu_page);\
    lv_obj_clear_flag(name##_panel, LV_OBJ_FLAG_SCROLLABLE);\
    lv_obj_set_size(name##_panel, lv_obj_get_width(ui_menu_page), PANEL_HEIGHT);\
    lv_obj_align(name##_panel, LV_ALIGN_TOP_MID, 0,/*dir * disp_width,*/ (id) * PANEL_HEIGHT);/*hide first then play anim*/\
    lv_obj_set_style_bg_color(name##_panel, lv_color_hex(PNAEL_COLOR), LV_STATE_DEFAULT);\
    lv_obj_set_style_bg_color(name##_panel, lv_color_hex(PNAEL_PRESSED_COLOR), LV_STATE_PRESSED);\
    lv_obj_set_style_border_color(name##_panel, lv_color_hex(0xffffff), LV_STATE_DEFAULT);\
    lv_obj_set_style_radius(name##_panel, 0, LV_STATE_DEFAULT);\
    lv_obj_set_style_border_side(name##_panel, LV_BORDER_SIDE_BOTTOM, LV_STATE_DEFAULT);\
    /*name##_icon*/\
    name##_icon = lv_label_create(name##_panel);\
    lv_obj_align(name##_icon, LV_ALIGN_LEFT_MID, 20, 0);\
    lv_obj_set_style_text_color(name##_icon, lv_color_hex(0xffffff), LV_STATE_DEFAULT);\
    lv_label_set_text(name##_icon, symbol);\
    /*name##_label*/\
    name##_label = lv_label_create(name##_panel);\
    lv_obj_align_to(name##_label, name##_icon, LV_ALIGN_OUT_RIGHT_MID, 20, 0);\
    lv_obj_set_style_text_color(name##_label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);\
    lv_label_set_text(name##_label, #name);\
		lv_obj_add_event_cb(name##_panel, event_##name##_panel_cb, LV_EVENT_CLICKED, NULL);\
		}while(0);
    /*name##_lv_anim_t*/\
    /*lv_anim_t name##_anim;\
    lv_anim_init(&name##_anim);\
    lv_anim_set_custom_exec_cb(&name##_anim,name##_anim_cb);\
    lv_anim_set_values(&name##_anim, 0, 100);\
    lv_anim_set_time(&name##_anim, ANIM_TIME);\
    lv_anim_set_delay(&name##_anim, ANIM_DELAY);\
    lv_anim_start(&name##_anim);\*/


/////////////////////////////////////////////////////////////////////////////////////////////////
    PANEL_LIST
    #undef X
    // lv_obj_add_event_cb(file_manage_panel, event_file_manage_cb, LV_EVENT_CLICKED, NULL);
    // lv_obj_add_event_cb(txt_read_panel, event_txt_read_cb, LV_EVENT_CLICKED, NULL);
    // lv_obj_add_event_cb(stop_watch_panel, event_stop_watch_cb, LV_EVENT_CLICKED, NULL);
    // lv_obj_add_event_cb(music_panel, event_music_cb, LV_EVENT_CLICKED, NULL);

}
static void menu_page_deinit(void){

}
