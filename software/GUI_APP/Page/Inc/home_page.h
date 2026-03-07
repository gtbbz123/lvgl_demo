#ifndef __HOME_PAGE_H
#define __HOME_PAGE_H
#include <stdint.h>
#include "./page_manage.h"
typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
}Date_Time_t;//    缓冲区，存放硬件获取的时间

extern Page_t home_page;
extern lv_obj_t *ui_home_page;
#endif