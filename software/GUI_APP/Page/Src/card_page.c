#include"../Inc/card_page.h"

#if (USE_HW == 0)
#include <stdio.h>
#endif 

//#define DEBUG_CARD_PAGE
#ifdef DEBUG_CARD_PAGE
#define CARD_PAGE_DEBUG(x) do {printf("[%s,%d]", __FILE__, __LINE__); printf x ;}while(0)
#else 
#define CARD_PAGE_DEBUG(x)
#endif

lv_obj_t *ui_card_page;

static void card_page_init(void);
static void card_page_deinit(void);
Page_t card_page = {card_page_init, card_page_deinit, &ui_card_page};

static void card_page_init(void){
    ui_card_page = lv_obj_create(NULL);
}
static void card_page_deinit(void){

}