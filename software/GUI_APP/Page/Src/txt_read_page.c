#include"../Inc/txt_read_page.h"

#if (USE_HW == 0)
#include <stdio.h>
#endif 

//#define DEBUG_TXT_READ_PAGE
#ifdef DEBUG_TXT_READ_PAGE
#define TXT_READ_PAGE_DEBUG(x) do {printf("[%s,%d]", __FILE__, __LINE__); printf x ;}while(0)
#else 
#define TXT_READ_PAGE_DEBUG(x)
#endif


#define FONT_COLOR 0x000000
#define BAKCGROUND_COLOR 0xffffff

#define ROW_MAX 20
#define COLUMN_MAX 4

#define TEXT_BUF_SIZE 512

text_manage_t  text_manage;

lv_obj_t *ui_txt_read_page;
static lv_obj_t *text_label;

static void txt_read_page_init(void);
static void txt_read_page_deinit(void);
static void refresh_text(uint8_t page);
static void event_change_page(lv_event_t *e);
Page_t txt_read_page = {txt_read_page_init, txt_read_page_deinit, &ui_txt_read_page};



lv_fs_file_t f;
lv_fs_res_t res;
uint32_t br;
extern lv_font_t chinese;

static char buf[2 * TEXT_BUF_SIZE];
static void txt_read_page_init(void){
    ui_txt_read_page = lv_obj_create(NULL);

    text_label = lv_label_create(ui_txt_read_page);
    lv_obj_set_style_text_font(text_label, &chinese, LV_STATE_DEFAULT);
    lv_obj_set_size(text_label, lv_obj_get_width(ui_txt_read_page), lv_obj_get_height(ui_txt_read_page));
    res = lv_fs_open(&f ,"0:/txt/abc.txt", LV_FS_MODE_RD);

    // printf("res = %d\n",res);
    // return ;
        refresh_text(0);

    lv_obj_add_event_cb(ui_txt_read_page, event_change_page, LV_EVENT_GESTURE, NULL);
    //lv_fs_close(&f);




}
static void txt_read_page_deinit(void){

}

static void refresh_text(uint8_t page){//Refresh the text according to the page number.
    uint32_t p = 0;
    uint32_t i = 0;
    char *file_buf = lv_mem_alloc(TEXT_BUF_SIZE * sizeof(char));
    if(page < 0 || page > PAGE_MAX){
        TXT_READ_PAGE_DEBUG("page is not exist\n");
        return;
    }
    if(text_manage.page_size[page] == 0){
        lv_fs_read(&f, file_buf, TEXT_BUF_SIZE - 1,&br);
        file_buf[br]  = 0;   
        for(i = 0; i < TEXT_BUF_SIZE; i++){
            if(file_buf[i] == '\n' || file_buf[i] == '\r'){
                memset(buf + p, ' ', p % COLUMN_MAX);
                p +=p % COLUMN_MAX;
                buf[p] = file_buf[i];
                p++;
            }
            else{
                buf[p] = file_buf[i];
                p++;
            }
        }
        buf[p] = 0;
        lv_label_set_text(text_label, buf);
    }

    lv_mem_free(file_buf);
    }

static void event_change_page(lv_event_t *e){
    lv_dir_t dir;
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_GESTURE){
        dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        if(dir == LV_DIR_LEFT)
            refresh_text(1);
    }
}