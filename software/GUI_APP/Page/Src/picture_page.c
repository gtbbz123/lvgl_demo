#include"../Inc/picture_page.h"

#if (USE_HW == 0)
#include <stdio.h>
#endif 

//#define DEBUG_PICTURE_PAGE
#ifdef DEBUG_PICTURE_PAGE
#define PICTURE_PAGE_DEBUG(x) do {printf("[%s,%d]", __FILE__, __LINE__); printf x ;}while(0)
#else 
#define PICTURE_PAGE_DEBUG(x)
#endif

lv_obj_t *ui_picture_page;

static void picture_page_init(void);
static void picture_page_deinit(void);
Page_t picture_page = {picture_page_init, picture_page_deinit, &ui_picture_page};

static void picture_page_init(void){
    ui_picture_page = lv_obj_create(NULL);
}
static void picture_page_deinit(void){

}