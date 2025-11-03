#include<stdio.h>
#include"imgprocess.h"

#ifndef PIXELS
  #include"utils.h"
#endif

#ifndef size_t
  #include<stdlib.h>
#endif

FILE *fp;
PIXELS pixels;
pixel_c size;
pixel_c w;
pixel_c h;

int main(int argc, char **argv) {
  if (argc <= 3) {
    fprintf(stderr, "Not enough arguments given!\n");
    return 1;
  }

  for (int i = 2; (i < argc) && !sscanf(argv[i], "--pixels=%lu", &size); i++);

  if (!size) {
    fprintf(stderr, "Please specify the no. of pixels!\n");
    return 1; 
  }

  pixels = (PIXELS) malloc(size * 3);

  if ((fp = fopen(argv[1], "rb")) == NULL) {
    fprintf(stderr, "Something went wrong while opening the file!\n");
    return 1;
  }

  read_pixels(pixels, fp, size);

  return 0;
}
