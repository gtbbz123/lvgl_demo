#include"../Inc/page_manage.h"
#include "../Inc/calendar_page.h"

#if (USE_HW == 0)
#include <stdio.h>
#endif 

//#define DEBUG_CALENDAR_PAGE
#ifdef DEBUG_CALENDAR_PAGE
#define CALENDAR_PAGE_DEBUG(x) do {printf("[%s,%d]", __FILE__, __LINE__); printf x ;}while(0)
#else 
#define CALENDAR_PAGE_DEBUG(x)
#endif


lv_obj_t *ui_calendar_page;

static void calendar_page_init(void);
static void calendar_page_deinit(void);
Page_t calendar_page = {calendar_page_init, calendar_page_deinit, &ui_calendar_page};

static void calendar_page_init(void){
    ui_calendar_page = lv_obj_create(NULL);
}
static void calendar_page_deinit(void){

}