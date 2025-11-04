#ifndef FILE
  #include<stdio.h>
#endif

#ifndef KERNEL_ORD
  #include"utils.h"
#endif

void img_blur() {
  float kernel[KERNEL_ORD][KERNEL_ORD] = { 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9, 1.0/9 };
  perform_convolution(kernel);
  write_pixels();
}

void hrz_edge_det() {
  float kernel[KERNEL_ORD][KERNEL_ORD] = { -1.0/4, 0, 1.0/4, 0, 0, 0, -1.0/4, 0, 1.0/4 };
  perform_convolution(kernel);
  write_pixels();
}
