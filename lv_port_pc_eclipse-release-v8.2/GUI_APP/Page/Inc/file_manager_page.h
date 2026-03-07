#ifndef __FILE_MANAGER_PAGE_H
#define __FILE_MANAGER_PAGE_H
#include "../../../lvgl/lvgl.h"
#include "./page_manage.h"


extern Page_t file_manager_page;
void FILE_MANAGER_file_open(const char *path, lv_obj_t *parent);
int FILE_MANAGER_DirectoryContents(const char* path, char* buf, uint32_t bufSize);


#endif
