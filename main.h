#define MAIN_INCLUDED 0

#include<stdio.h>
#include"imgprocess.h"

#ifndef PIXELS
  #include"utils.h"
#endif

extern FILE *fp;
extern char ofname[256];
extern PIXELS pixels;
extern pixel_c size;
extern pixel_c w;
extern pixel_c h;
