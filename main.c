#include<stdio.h>
#include"imgprocess.h"

#ifndef PIXELS
  #include"utils.h"
#endif

#ifndef size_t
  #include<stdlib.h>
#endif

#ifndef __STRING_H_SOURCED__
  #include<string.h>
#endif

FILE *fp;
char ofname[256];
PIXELS pixels;
pixel_c size;
pixel_c w;
pixel_c h;

int main(int argc, char **argv) {
  char ifname[256];
  int i = 0;

  if (argc <= 3) {
    fprintf(stderr, "Not enough arguments given!\n");
    return 1;
  }

  for (i = 1; (i < argc) && !sscanf(argv[i], "--size=%lux%lu", &w, &h); i++);

  for (i = 1; (i < argc); i++)
    if (sscanf(ifname, "--size=%lux%lu", &w, &h)) continue;
    else {
      sscanf(argv[i], "%[^\n]s", ifname);
      break;
    };

  for (i = i + 1; (i < argc); i++)
    if (sscanf(ifname, "--size=%lux%lu", &w, &h)) continue;
    else {
      sscanf(argv[i], "%[^\n]s", ofname);
      break;
    };

  if (!w || !h) {
    fprintf(stderr, "Please specify the size!\n");
    return 1; 
  }

  if (!strcmp(ifname, "\0") || !strcmp(ofname, "\0")) {
    fprintf(stderr, "Please specify the input and output file names!\n");
    return 1; 
  }

  size = w * h;
  pixels = (PIXELS) malloc(size * 3);

  if ((fp = fopen(ifname, "rb")) == NULL) {
    fprintf(stderr, "Something went wrong while opening the file!\n");
    return 1;
  }

  read_pixels();
  img_blur  ();

  return 0;
}
