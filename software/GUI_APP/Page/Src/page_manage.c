#include "../Inc/page_manage.h"

#if (USE_HW == 0)
#include <stdio.h>
#endif 

//#define DEBUG_PAGE_MANAGE
#ifdef DEBUG_PAGE_MANAGE
#define PAGE_MANAGE_DEBUG(x) do {printf("[%s,%d]", __FILE__, __LINE__); printf x ;}while(0)
#else 
#define PAGE_MANAGE_DEBUG(x)
#endif


static Page_Stack_t page_stack;


void PAGE_MANAGE_page_push(Page_t *page){
    if(page_stack.stack_top == PAGE_STACK_DEEP){
        PAGE_MANAGE_DEBUG(("PAGE STACK OVERFLOW!\n"));
        return;
}
    page_stack.page_stack[page_stack.stack_top] = page;
    page_stack.stack_top++;
    return ;
}
Page_t *PAGE_MANAGE_page_pop(void){
    Page_t *page = {0};
    if(page_stack.stack_top == 0){
        PAGE_MANAGE_DEBUG(("PAGE STACK IS EMPTY!\n"));
        return page;
    }
    page_stack.stack_top--;
    page = page_stack.page_stack[page_stack.stack_top];
    return page;
}
void PAGE_MANAGE_page_init(void){
    page_stack.stack_top = 0;
}

void PAGE_MANAGE_page_load(Page_t *page){
    if(page == NULL) return ;
    if(page_stack.stack_top == 0){
        PAGE_MANAGE_DEBUG(("PAGE STACK IS EMPTY!\n"));
        return ;
    }
    page_stack.page_stack[page_stack.stack_top - 1]->deinit();
    PAGE_MANAGE_page_push(page);
    page->init();
    lv_scr_load_anim(*page->page_obj, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 100, 0, true);
    


}