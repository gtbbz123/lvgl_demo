#include "../Inc/file_manager_page.h"
#include <string.h>
#if (USE_HW == 0)
#include <stdio.h>
#endif 

//#define DEBUG_FILE_MANAGE_PAGE
#ifdef DEBUG_FILE_MANAGE_PAGE
#define FILE_MANAGE_PAGE_DEBUG(x) do {printf("[%s,%d]", __FILE__, __LINE__); printf x ;}while(0)
#else 
#define FILE_MANAGE_PAGE_DEBUG(x)
#endif


static void file_manager_page_init(void);
static void file_manager_page_deinit(void);


static void event_list_btn(lv_event_t *e);
static void event_list_ret(lv_event_t *e);


char root_path[] = "0:/";

lv_obj_t *ui_file_manager_page;
static lv_obj_t *list;
static char current_path[128];
Page_t file_manager_page = {file_manager_page_init, file_manager_page_deinit, &ui_file_manager_page};



static char buf[512];
static void file_manager_page_init(void){
    ui_file_manager_page = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(ui_file_manager_page, lv_color_hex(PAGE_COLOR), LV_STATE_DEFAULT);

    FILE_MANAGER_file_open("0:/", ui_file_manager_page);
}
static void file_manager_page_deinit(void){

}

void FILE_MANAGER_file_open(const char *path, lv_obj_t *parent){
    uint16_t count;
    if(list != NULL)
    lv_obj_del(list);

    list = lv_list_create(parent);
    lv_obj_set_style_pad_all(list, 0, 0); 
    lv_obj_set_style_pad_row(list, 0, 0); 
    lv_obj_set_style_bg_color(list, lv_color_hex(PAGE_COLOR), LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(list, 0, LV_STATE_DEFAULT);

    
    lv_obj_set_size(list, lv_obj_get_width(parent), lv_obj_get_height(parent));


    //the btn for close
    lv_obj_t *ret = lv_label_create(parent);
    lv_obj_set_style_bg_color(ret, lv_color_hex(PAGE_COLOR), LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ret, lv_color_hex(0xdddddd), LV_STATE_PRESSED);
    lv_obj_set_style_text_color(ret, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_obj_add_flag(ret, LV_OBJ_FLAG_CLICKABLE);
    lv_label_set_text(ret, LV_SYMBOL_UP);
    lv_obj_align(ret, LV_ALIGN_TOP_RIGHT, -10, 8);
    lv_obj_add_event_cb(ret, event_list_ret, LV_EVENT_PRESSED, parent);


    strcpy(current_path, path);
    //set headline
    lv_obj_t *headline;
    //char str[64] = {0};
    // strcat(str, LV_SYMBOL_DIRECTORY);
    // strcat(str, "   ");
    // strcat(str, c + 1);
    headline = lv_list_add_text(list, path);
    lv_obj_set_height(headline, 30);
    lv_obj_set_style_bg_color(headline, lv_color_hex(PAGE_COLOR), LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(headline, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(headline, LV_BORDER_SIDE_BOTTOM, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(headline, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(headline,2, LV_STATE_DEFAULT);

    count =FILE_MANAGER_DirectoryContents(path, buf, sizeof(buf));
    //printf("%s",buf);


    char *token;
    char *saveptr = buf;
    char symbol[4];
    lv_obj_t **files = (lv_obj_t **)lv_mem_alloc(sizeof(lv_obj_t *) * 3);
    for(int i = 0; i < count; i++){
        //select icon
        token = strtok_r(NULL, "\n", &saveptr);
        if(strstr(token, ".txt")){
            strcpy(symbol,LV_SYMBOL_FILE);
        }
        else if(strstr(token, ".mp3")){
            strcpy(symbol,LV_SYMBOL_AUDIO);
        }
        else if(strstr(token, ".bin")){
            strcpy(symbol,LV_SYMBOL_PLAY);
        }
        else{
            strcpy(symbol,LV_SYMBOL_DIRECTORY);
        }
        // add btn to list
        files[i] = lv_list_add_btn(list, symbol, token);
        lv_obj_set_height(files[i], 40);
        lv_obj_set_style_bg_color(files[i], lv_color_hex(PAGE_COLOR), LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(files[i], lv_color_hex(0xffffff), LV_STATE_DEFAULT);
        lv_obj_set_style_border_side(files[i], LV_BORDER_SIDE_BOTTOM, LV_STATE_DEFAULT);
        lv_obj_set_style_border_color(files[i], lv_color_hex(0xffffff), LV_STATE_DEFAULT);
        lv_obj_set_style_border_width(files[i],1, LV_STATE_DEFAULT);
        //only add directory
        if(!strcmp(symbol,LV_SYMBOL_DIRECTORY))
        lv_obj_add_event_cb(files[i], event_list_btn, LV_EVENT_PRESSED, parent);
    }
    lv_mem_free(files);
}

static void event_list_btn(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    char path[128] = {0};
    lv_obj_t * ui = (lv_obj_t *)lv_event_get_user_data(e);
    if(code == LV_EVENT_PRESSED){
        const char *text = lv_list_get_btn_text(list, obj);
        strcat(path,current_path);
        strcat(path,text);
        FILE_MANAGER_file_open(path, ui);
    }
}

static void event_list_ret(lv_event_t *e){
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    lv_obj_t *ui = (lv_obj_t *)lv_event_get_user_data(e);
    char path[128];
    strcpy(path,current_path);
    if(code == LV_EVENT_PRESSED){
        if(!strcmp(root_path, current_path)){
            return;
        }
        char* end = strrchr(path, '/');
        *end = 0;
        FILE_MANAGER_file_open(path, ui);
    }
}
int FILE_MANAGER_DirectoryContents(const char* path, char* buf, uint32_t bufSize) {
    // 检查参数
    if (path == NULL || path[0] == '\0' || buf == NULL || bufSize == 0) {
        return -1;  // 无效参数
    }
    
    // 清空缓冲区
    buf[0] = '\0';
    
    // 检查驱动器是否就绪（如果有驱动器字母）
    if (path[1] == ':') {  // 格式如 "C:/path"
        char drive_letter = path[0];
        if (!lv_fs_is_ready(drive_letter)) {
            return -2;  // 驱动器未就绪
        }
    }
    
    // 打开目录
    lv_fs_dir_t dir;
    lv_fs_res_t res = lv_fs_dir_open(&dir, path);
    if (res != LV_FS_RES_OK) {
        return -3;  // 打开目录失败
    }
    
    uint32_t currentLength = 0;
    int fileCount = 0;
    char filename[LV_FS_MAX_FN_LENGTH];
    
    // 遍历目录
    while (1) {
        // 读取下一个条目
        res = lv_fs_dir_read(&dir, filename);
        if (res != LV_FS_RES_OK) {
            // 读取错误
            break;
        }
        
        // LVFS读取结束时返回空字符串
        if (filename[0] == '\0') {
            break;
        }
        
        // 跳过当前目录(.)和父目录(..)
        if (strcmp(filename, ".") == 0 || strcmp(filename, "..") == 0) {
            continue;
        }
        
        // 去除末尾的 '/' 字符（如果是目录）
        size_t filename_len = strlen(filename);
        if (filename_len > 0 && filename[filename_len - 1] == '/') {
            filename[filename_len - 1] = '\0';  // 去掉末尾的 '/'
            filename_len--;  // 更新长度
        }
        
        // 检查缓冲区是否足够（文件名 + 换行符 + 现有内容 + 结尾空字符）
        if (currentLength + filename_len + 2 > bufSize) {
            // 缓冲区不足，关闭目录并返回负数
            lv_fs_dir_close(&dir);
            return -(fileCount + 1);  // 负数表示缓冲区不足，绝对值表示已处理数量
        }
        
        // 追加文件名到缓冲区
        strcpy(buf + currentLength, filename);
        currentLength += filename_len;
        
        // 追加换行符
        buf[currentLength] = '\n';
        currentLength++;
        
        fileCount++;
    }
    
    // 确保缓冲区以空字符结尾
    buf[currentLength] = '\0';
    
    // 关闭目录
    lv_fs_dir_close(&dir);
    
    return fileCount;  // 返回文件个数
}