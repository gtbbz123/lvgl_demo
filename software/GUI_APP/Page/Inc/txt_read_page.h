#ifndef __TXT_READ_PAGE_H
#define __TXT_READ_PAGE_H

#include "../../../lvgl/lvgl.h"
#include "../Inc/page_manage.h"

#define PAGE_MAX 32
typedef struct{
uint32_t current_page;
uint32_t page_size[PAGE_MAX];//page_max is 32
}text_manage_t;

extern Page_t txt_read_page;
#endif 
