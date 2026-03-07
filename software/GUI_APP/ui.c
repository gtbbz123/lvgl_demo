#include "ui.h"
#include "./Page/Inc/page_manage.h"
#include "./Page/Inc/home_page.h"
#include "uart.h"
void UI_init(void){
			PAGE_MANAGE_page_init();
    PAGE_MANAGE_page_push(&home_page);
    home_page.init();
    lv_scr_load(ui_home_page);
}