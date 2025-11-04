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

// -1.0/4, -0.5, 1.0/4, 0, 0, 0, 1.0/4, 0.5, 1.0/4 gives a kind of precise edge detection
// -1.0/4, -0.5, -1.0/4, 0, 0, 0, 1.0/4, 0.5, 1.0/4 This too
// Doesn't detect edge 1.0/4, 0.5, 1.0/4, 0, 0, 0, -1.0/4, -0.5, -1.0/4
// 1.0/4, 0.5, 1.0/4, 0, 0, 0, 1.0/4, 0.5, 1.0/4 Thermal camera
// -1.0/4, -0.5, -1.0/4, 0, 0, 0, -1.0/4, -0.5, -1.0/4 Another kind of thermal camera
// -1.0/4, 0, -1.0/4, 0, 0, 0, -1.0/4, 0, -1.0/4 Perfect foreground detector (Actually negative filter)
// 1.0/4, 0, -1.0/4, 0, 0, 0, -1.0/4, 0, 1.0/4 gives depth to edge like 3D
// -1.0/4, 0, 1.0/4, 0, 0, 0, 1.0/4, 0, -1.0/4 This too similar to above

// 1.0/4, 0, -1.0/4, 0.5, 0, -0.5, 1.0/4, 0, -1.0/4 3b1b (Sketchy art)

void hrz_edge_det() {
  float kernel[KERNEL_ORD][KERNEL_ORD] = { 1.0/4, 0, -1.0/4, 0.5, 0, -0.5, 1.0/4, 0, -1.0/4 };
  perform_convolution(kernel);
  write_pixels();
}
