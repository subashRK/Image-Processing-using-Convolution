#ifndef KERNEL_ORD
  #include"utils.h"
#endif

#ifndef size_t
  #include<stdlib.h>
#endif

#ifndef FILE
  #include<stdio.h>
#endif

#ifndef MAIN_INCLUDED
  #include"main.h"
#endif

void allocate_prev_pixels(PIXELS surr_pixels, pixel_c curr_pix, PIXEL color) {
  pixel_c current_row = curr_pix / w;
  pixel_c current_col = (curr_pix) % w;

  for (int i = -1; i <= 1; i++) {
    for (int j = -1; i <= 1; j++) {
      if (
        current_row + i < 0 || current_row + i > h - 1 ||
        current_col + j < 0 || current_col + j > w - 1 
      ) {
        surr_pixels[i + 1][j + 1] = 0;
        continue;
      }

      surr_pixels[i + 1][j + 1] = pixels[curr_pix + i * w + j][color];
    }
  }
}

int convolution(float (*kernel)[3]) {
  PIXEL pixel[3];

  for (pixel_c i = 0; i < size; i++) {
    pixel[0] = pixels[0];
    pixel[1] = pixels[1];
    pixel[2] = pixels[2];

    PIXELS surr_pixels_r = (PIXELS) malloc(9);
    PIXELS surr_pixels_g = (PIXELS) malloc(9);
    PIXELS surr_pixels_b = (PIXELS) malloc(9);

    allocate_prev_pixels(surr_pixels_r, i, 0);
    allocate_prev_pixels(surr_pixels_g, i, 1);
    allocate_prev_pixels(surr_pixels_b, i, 2);

    pixels[i][0] = convolved_val(surr_pixels_r, kernel);
    pixels[i][1] = convolved_val(surr_pixels_g, kernel);
    pixels[i][2] = convolved_val(surr_pixels_b, kernel);
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

void read_pixels() {
  pixel_c i = 0;

  while (!fread((pixels + i++), 1, 3, fp)) {
    if (i == size) return;

    if (i > size) {
      fprintf(stderr, "Please give the right no. of pixels!\n");
      exit(1);
    }

  }
}
