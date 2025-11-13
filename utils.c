#ifndef KERNEL_ORD
  #include"utils.h"
#endif

#ifndef size_t
  #include<stdlib.h>
#endif

#ifndef __STRING_H_SOURCED__
  #include<string.h>
#endif

#ifndef FILE
  #include<stdio.h>
#endif

#ifndef MAIN_INCLUDED
  #include"main.h"
#endif

static PIXELS temp_pixels;

void allocate_prev_pixels(PIXELS surr_pixels, pixel_c curr_pix, pixel_c color) {
  pixel_c current_row = curr_pix / w;
  pixel_c current_col = (curr_pix) % w;

  for (int i = -1; i <= 1; i++) 
  {
    for (int j = -1; j <= 1; j++) 
    {
      if (
        (((long int) current_row + i) < 0) || (((long int) current_row + i) > (h - 1)) ||
        (((long int) current_col + j) < 0) || (((long int) current_col + j) > (w - 1))
      ) {
        surr_pixels[i + 1][j + 1] = pixels[curr_pix][color];
        continue;
      }
    
      surr_pixels[i + 1][j + 1] = pixels[curr_pix + (i * w) + j][color];
    }
  }
}

PIXEL convolved_val(PIXELS surr_pixels, float (*kernel)[3]) {
  float val = 0;

  for (int i = 0; i < KERNEL_ORD; i++)
    for (int j = 0; j < KERNEL_ORD; j++)
      val += (surr_pixels[i][j] * kernel[i][j]);

  return (PIXEL) val;
}

void perform_convolution(float (*kernel)[3]) {
  if (temp_pixels) free(temp_pixels); 
  temp_pixels = (PIXELS) malloc(size * 3);

  for (pixel_c i = 0; i < size; i++) 
  {
    PIXELS surr_pixels_r = (PIXELS) malloc(9);
    PIXELS surr_pixels_g = (PIXELS) malloc(9);
    PIXELS surr_pixels_b = (PIXELS) malloc(9);

    allocate_prev_pixels(surr_pixels_r, i, 0);
    allocate_prev_pixels(surr_pixels_g, i, 1);
    allocate_prev_pixels(surr_pixels_b, i, 2);

    temp_pixels[i][0] = convolved_val(surr_pixels_r, kernel);
    temp_pixels[i][1] = convolved_val(surr_pixels_g, kernel);
    temp_pixels[i][2] = convolved_val(surr_pixels_b, kernel);
  }
}

void write_gray_pixels(PIXEL gray_pixels[size]) {
  if (fp) {
    fclose(fp);
    fp = NULL;
  };

  FILE *ofp = fopen(ofname, "wb");

  if (!ofp) {
    fprintf(stderr, "Can't write content to output file!\n");
    exit(1);
  }

  fwrite(gray_pixels, size, 1, ofp);
  fclose(ofp);
}

void read_pixels() {
  pixel_c i = 0;

  while (fread((pixels + i++), 3, 1, fp)) 
  {
    if (i == size) 
      return;
  }

  if (i < size) {
    fprintf(stderr, "Please give the right no. of pixels!\n");
    exit(1);
  }
}

void write_pixels() {
  if (fp) {
    fclose(fp);
    fp = NULL;
  };

  FILE *ofp = fopen(ofname, "wb");

  if (!ofp) {
    fprintf(stderr, "Can't write content to output file!\n");
    exit(1);
  }

  fwrite(temp_pixels, size * 3, 1, ofp);
  fclose(ofp);
}
