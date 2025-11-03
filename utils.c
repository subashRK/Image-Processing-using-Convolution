#ifndef KERNEL_ORD
  #include"utils.h"
#endif

#ifndef size_t
  #include<stdlib.h>
#endif

#ifndef FILE
  #include<stdio.h>
#endif

int allocate_prev_pixels(PIXELS pixels, PIXELS surr_pixels, pixel_c i) {
  
}

int convolution(PIXELS pixels, float (*kernel)[3], pixel_c size) {
  PIXEL pixel[3];

  for (pixel_c i = 0; i < size; i++) {
    pixel[0] = pixels[0];
    pixel[1] = pixels[1];
    pixel[2] = pixels[2];

    for (int j = 1; j < 3; j++)
      for (int k = 1; k < 3; k++) {
        PIXELS surr_pixels_r = (PIXELS) malloc(9);
        PIXELS surr_pixels_g = (PIXELS) malloc(9);
        PIXELS surr_pixels_b = (PIXELS) malloc(9);

        pixels[i][0] = convolved_val(surr_pixels_r, kernel);
        pixels[i][1] = convolved_val(surr_pixels_g, kernel);
        pixels[i][2] = convolved_val(surr_pixels_b, kernel);
      }
  }
}

PIXEL convolved_val(PIXELS surr_pixels, float (*kernel)[3]) {
  PIXEL val = 0;

  for (int i = 0; i < KERNEL_ORD; i++) {
    for (int j = 0; j < KERNEL_ORD; j++) {
      val += surr_pixels[i][j] * kernel[i][j];
    }
  }

  return val;
}

void read_pixels(PIXELS pixels, FILE *fp, pixel_c size) {
  pixel_c i = 0;

  while (!fread((pixels + i++), 1, 3, fp)) {
    if (i == size) return;

    if (i > size) {
      fprintf(stderr, "Please give the right no. of pixels!\n");
      exit(1);
    }

  }
}
