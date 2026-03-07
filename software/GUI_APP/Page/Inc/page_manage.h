#ifndef __page_manage_H
#define __page_manage_H
#include "../../../lvgl/lvgl.h"

#define PAGE_STACK_DEEP 5

#define PAGE_COLOR 0x000000

typedef struct {
    void (*init)(void);
    void (*deinit)(void);
    lv_obj_t **page_obj;
}Page_t;
typedef struct
{
    Page_t *page_stack[PAGE_STACK_DEEP];
    uint8_t stack_top;
}Page_Stack_t;

void PAGE_MANAGE_page_push(Page_t *page);
Page_t *PAGE_MANAGE_page_pop(void);
void PAGE_MANAGE_page_init(void);
void PAGE_MANAGE_page_load(Page_t *page);

#endif

