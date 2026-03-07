#include"../Inc/device_info_page.h"

#if (USE_HW == 0)
#include <stdio.h>
#endif 

//#define DEBUG_DEVICE_INFO_PAGE
#ifdef DEBUG_DEVICE_INFO_PAGE
#define DEVICE_INFO_PAGE_DEBUG(x) do {printf("[%s,%d]", __FILE__, __LINE__); printf x ;}while(0)
#else 
#define DEVICE_INFO_PAGE_DEBUG(x)
#endif

lv_obj_t *ui_device_info_page;

static void device_info_page_init(void);
static void device_info_page_deinit(void);
Page_t device_info_page = {device_info_page_init, device_info_page_deinit, &ui_device_info_page};

static void device_info_page_init(void){
    ui_device_info_page = lv_obj_create(NULL);
}
static void device_info_page_deinit(void){

}