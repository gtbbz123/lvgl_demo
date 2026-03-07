#ifndef __HW_INTERFACE_H
#define __HW_INTERFACE_H
#include <stdint.h>




#define USE_HW 0
//#define DEBUG_CALENDAR_PAGE
#ifdef DEBUG_HW_INTERFACE
#define HW_INTERFACE_DEBUG(x) do {printf("[%s,%d]", __FILE__, __LINE__); printf x ;}while(0)
#else 
#define HW_INTERFACE_DEBUG(x)
#endif

typedef struct{
    int (*GetDirectoryContents)(const char* path, char* buf, uint32_t bufSize);
}hw_file_t;



typedef struct{
    hw_file_t hw_file_interface;
}hw_interface_t;



extern hw_interface_t hw_interface;
#endif
