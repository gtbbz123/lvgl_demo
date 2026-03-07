#include "../Inc/home_page.h"
#include "../../../lvgl/lvgl.h"
#include "../../ui_helper/Inc/font_border.h"
#include "../Inc/page_manage.h"
#include "../Inc/calculator_page.h"
#include "../../HardwareInterface/HW_interface.h"
#include "../Inc/menu_page.h"

#if (USE_HW == 0)
#include <stdio.h>
#endif 

//#define DEBUG_HOME_PAGE
#ifdef DEBUG_HOME_PAGE
#define HOME_PAGE_DEBUG(x) do {printf("[%s,%d]", __FILE__, __LINE__); printf x ;}while(0)
#else 
#define HOME_PAGE_DEBUG(x)
#endif


#define TIME_POS_X 5
#define TIME_POS_Y 100

#define DATE_POS_X 0
#define DATE_POS_Y 64

#define FONT_COLOR 0xffffff
#define FONT_BORDOR_COLOR 0x666666



lv_obj_t *ui_home_page;
static lv_obj_t *time;
static lv_obj_t *date;

static Date_Time_t date_time_buf;

static void home_page_deinit(void);
static void home_page_init(void);
static void event_home_page_cb(lv_event_t *e);

Page_t home_page = {home_page_init, home_page_deinit, &ui_home_page};

static void home_page_deinit(void){
    return ;
}

static void home_page_init(void){
    //test
    date_time_buf.hour = 12;
    date_time_buf.year = 2026;
    date_time_buf.month = 2;
    date_time_buf.day = 22;

    //page
    ui_home_page = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(ui_home_page, lv_color_hex(PAGE_COLOR), LV_STATE_DEFAULT);
    lv_obj_clear_flag(ui_home_page, LV_OBJ_FLAG_SCROLLABLE);


    //time
    time = lv_label_create(ui_home_page);
    lv_obj_align(time, LV_ALIGN_TOP_MID, TIME_POS_X, TIME_POS_Y);
    lv_obj_set_style_text_font(time, &lv_font_montserrat_38, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(time, lv_color_hex(FONT_COLOR),LV_STATE_DEFAULT);
    lv_label_set_text_fmt(time, "%d : %02d ",date_time_buf.hour, date_time_buf.minute);

    lv_label_add_border(time, 2, lv_color_hex(FONT_BORDOR_COLOR), 0);

    //date
    date = lv_label_create(ui_home_page);
    lv_obj_align(date, LV_ALIGN_TOP_MID, DATE_POS_X, DATE_POS_Y);
    lv_obj_set_style_text_font(date, &lv_font_montserrat_38, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(date, lv_color_hex(FONT_COLOR),LV_STATE_DEFAULT);
    lv_label_set_text_fmt(date, "%04d/%02d/%02d",date_time_buf.year, date_time_buf.month, date_time_buf.day);

    lv_label_add_border(date, 2, lv_color_hex(FONT_BORDOR_COLOR), 0);

    lv_obj_add_event_cb(ui_home_page, event_home_page_cb, LV_EVENT_GESTURE, NULL);
}

static void event_home_page_cb(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_dir_t dir;
    if(code == LV_EVENT_GESTURE){
        dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        if(dir == LV_DIR_RIGHT)
        PAGE_MANAGE_page_load(&menu_page);
        HOME_PAGE_DEBUG(("dir = %d\n", dir));
    }
}