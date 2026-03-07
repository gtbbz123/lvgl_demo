#include"../Inc/game_page.h"

#if (USE_HW == 0)
#include <stdio.h>
#endif 

//#define DEBUG_GAME_PAGE
#ifdef DEBUG_GAME_PAGE
#define GAME_PAGE_DEBUG(x) do {printf("[%s,%d]", __FILE__, __LINE__); printf x ;}while(0)
#else 
#define GAME_PAGE_DEBUG(x)
#endif

lv_obj_t *ui_game_page;

static void game_page_init(void);
static void game_page_deinit(void);
Page_t game_page = {game_page_init, game_page_deinit, &ui_game_page};

static void game_page_init(void){
    ui_game_page = lv_obj_create(NULL);
}
static void game_page_deinit(void){

}