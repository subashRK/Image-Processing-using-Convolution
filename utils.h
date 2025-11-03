#ifndef FILE
  #include<stdio.h>
#endif

#define KERNEL_ORD 3

typedef unsigned char PIXEL;
typedef PIXEL (*PIXELS)[3];
typedef unsigned long int pixel_c;

void read_pixels(PIXELS, FILE *, pixel_c);
