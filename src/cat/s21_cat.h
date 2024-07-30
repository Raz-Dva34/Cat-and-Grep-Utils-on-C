#ifndef SRC_S21_CAT_H_
#define SRC_S21_CAT_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {  //Объявили структуру и перечислили все флаги которые есть
  int number_nonempty;
  int end_characters;
  int number_all_output;
  int squeeze_blank;
  int display_tab;
  int v;
} Options;

Options get_option(int argc, char *argv[]);
void file_open(int count, char *argv[], Options option);
void flags(Options option, int before, int counter, int c, int j, FILE *f);

#endif