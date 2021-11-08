#include "stock_utils.h"
#include "stock.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]){
  (void)argc;
  (void)argv;
  
  FILE *in_fp = fopen("input.txt", "r");
  if (in_fp == NULL){
    exit(EXIT_FAILURE);
  }

  FILE *out_fp = fopen("output.txt", "w");

  stock_init(out_fp);

  char * line = NULL;
  size_t len = 0;

  signal_t signal;
  while(getline(&line, &len, in_fp) != -1){
    stock_utils_parse_signal(line, &signal);
    stock_handle_signal(&signal);
  }

  stock_cleanup();

  fclose(in_fp);
  if (line){
    free(line);
  }

  fflush(out_fp);
  fclose(out_fp);


  exit(EXIT_SUCCESS);
}