#include"../Inc/stop_watch_page.h"

#if (USE_HW == 0)
#include <stdio.h>
#endif 

//#define DEBUG_STOP_WATCH
#ifdef DEBUG_STOP_WATCH
#define STOP_WATCH_DEBUG(x) do {printf("[%s,%d]", __FILE__, __LINE__); printf x ;}while(0)
#else 
#define STOP_WATCH_DEBUG(x)
#endif

lv_obj_t *ui_stop_watch_page;

static void stop_watch_page_init(void);
static void stop_watch_page_deinit(void);
Page_t stop_watch_page = {stop_watch_page_init, stop_watch_page_deinit, &ui_stop_watch_page};

static void stop_watch_page_init(void){
    ui_stop_watch_page = lv_obj_create(NULL);
}
static void stop_watch_page_deinit(void){

}