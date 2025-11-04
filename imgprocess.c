#ifndef FILE
  #include<stdio.h>
#endif

#ifndef KERNEL_ORD
  #include"utils.h"
#endif

void img_blur() {
  float kernel[KERNEL_ORD][KERNEL_ORD] = { 1/9, 1/9, 1/9, 1/9, 1/9, 1/9, 1/9, 1/9, 1/9 };
  perform_convolution(kernel);
  write_pixels();
}
