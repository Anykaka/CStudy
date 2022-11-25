#pragma PRINT_H

#include <stdio.h>	/* vsnprintf与vsprintf */
#include <stdarg.h>	/* va... */
#include <stdio.h>
#include <string.h>

#define DPRINT_SIZE     4096
#define DEBUG_PRINT     1


// 部分颜色代码:
// 字背景颜色: 40--49                字颜色: 30--39
// 40: 黑                           30: 黑
// 41: 红                           31: 红
// 42: 绿                           32: 绿
// 43: 黄                           33: 黄
// 44: 蓝                           34: 蓝
// 45: 紫                           35: 紫
// 46: 深绿                         36: 深绿
// 47：白色                         37：白色
#define DEBUG_BACK_COLOR    1   // 背景颜色
#define DEBUG_FONT_COLOR    33  // 字体颜色

char buf[DPRINT_SIZE];

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define DPRINT(_buf_, ...) print(__TIME__, __FILENAME__, __func__, __LINE__, _buf_, ##__VA_ARGS__);

void print(const char* time, const char* file, const char* func, int line, const char *f, ...);
