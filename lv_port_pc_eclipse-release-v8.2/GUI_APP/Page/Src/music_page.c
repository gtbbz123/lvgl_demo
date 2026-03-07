#include"../Inc/settings_page.h"

#if (USE_HW == 0)
#include <stdio.h>
#endif 

//#define DEBUG_MUSCI_PAGE
#ifdef DEBUG_MUSCI_PAGE
#define MUSCI_PAGE_DEBUG(x) do {printf("[%s,%d]", __FILE__, __LINE__); printf x ;}while(0)
#else 
#define MUSCI_PAGE_DEBUG(x)
#endif

lv_obj_t *ui_music_page;

static void music_page_init(void);
static void music_page_deinit(void);
Page_t music_page = {music_page_init, music_page_deinit, &ui_music_page};

static void music_page_init(void){
    ui_music_page = lv_obj_create(NULL);
}
static void music_page_deinit(void){

}