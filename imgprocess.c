#ifndef FILE
  #include<stdio.h>
#endif

#ifndef size_t
  #include<stdlib.h>
#endif

#ifndef __STRING_H_SOURCED__
  #include<string.h>
#endif

#ifndef MAIN_INCLUDED
  #include"main.h"
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
  float kernel[KERNEL_ORD][KERNEL_ORD] = { 
    1.0/4, 0, -1.0/4, 0.5, 0, -0.5, 1.0/4, 0, -1.0/4
  };
  perform_convolution(kernel);
  write_pixels();
}

void ver_edge_det() {
  float kernel[KERNEL_ORD][KERNEL_ORD] = { 
    -1.0/4, -0.5, -1.0/4, 0, 0, 0, 1.0/4, 0.5, 1.0/4
  };
  perform_convolution(kernel);
  write_pixels();
}

void gray_edge_det(PIXEL *gray_pixels, float (*kernel)[3]) {
  PIXEL neighbourhood[3][3];
  PIXEL temp_pixels[size];

  for (int curr_pix = 0; curr_pix < size; curr_pix++) {
    pixel_c current_row = curr_pix / w;
    pixel_c current_col = curr_pix % w;

    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (
          (((long int) current_row + i) < 0) || (((long int) current_row + i) > (h - 1)) ||
          (((long int) current_col + j) < 0) || (((long int) current_col + j) > (w - 1))
        ) {
          neighbourhood[i + 1][j + 1] = gray_pixels[curr_pix];
          continue;
        }
      
        neighbourhood[i + 1][j + 1] = gray_pixels[curr_pix + (i * w) + j];
      }
    }

    float val = 0;

    for (int i = 0; i < KERNEL_ORD; i++)
      for (int j = 0; j < KERNEL_ORD; j++) {
        val += (kernel[i][j] * neighbourhood[i][j]);
      }

    // temp_pixels[curr_pix] = 255 - val; /* for black border with white foreground */
    temp_pixels[curr_pix] = val;
  }

  write_gray_pixels(temp_pixels);
}

PIXEL *gen_gray_scale(PIXEL threshold) {
  PIXEL *gray_pixels = malloc(size);

  for (int i = 0; i < size; i++)
    // Threshold is used, so that the pixel value is a discrete value (either 0 or 255) not an analog value (from 0 to 255)
    gray_pixels[i] = 255 - (((((short int) pixels[i][0] + pixels[i][1] + pixels[i][2])/3) < threshold) * 255);
  
  return gray_pixels;
}

void bw_img() {
  float kernel[KERNEL_ORD][KERNEL_ORD] = { 
    1.0/4, 0, -1.0/4, 0.5, 0, -0.5, 1.0/4, 0, -1.0/4
  };
  PIXEL threshold = 128; // adjust threshold value to get different results
  PIXEL *gray_pixels = gen_gray_scale(threshold);

  gray_edge_det(gray_pixels, kernel);
}
