#ifndef FILE
  #include<stdio.h>
#endif

#define KERNEL_ORD 3

typedef unsigned char PIXEL;
typedef PIXEL (*PIXELS)[3];
typedef unsigned long int pixel_c;

void read_pixels();
void write_pixels();
void write_gray_pixels(PIXEL []);
void perform_convolution(float (*)[3]);
