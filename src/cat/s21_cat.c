#include "s21_cat.h"

int main(int argc, char *argv[]) {
  Options option = get_option(argc, argv);

  file_open(argc, argv, option);
  return 0;
}

Options get_option(int argc, char *argv[]) {
  static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                         {"number", 0, 0, 'n'},
                                         {"squeeze-blank", 0, 0, 's'},
                                         {0, 0, 0, 0}};
  int this_flag = getopt_long(argc, argv, "+bevEnstT", long_options, 0);
  Options option = {0, 0, 0, 0, 0, 0};
  for (; this_flag != -1;
       this_flag = getopt_long(argc, argv, "+bevEnstT", long_options, 0)) {
    switch (this_flag) {
      case 'b':
        option.number_nonempty = 1;
        break;
      case 'e':
        option.end_characters = 1;
        option.v = 1;
        break;
      case 'n':
        option.number_all_output = 1;
        break;
      case 's':
        option.squeeze_blank = 1;
        break;
      case 't':
        option.display_tab = 1;
        option.v = 1;
        break;
      case 'v':
        option.v = 1;
        break;
      case 'E':
        option.end_characters = 1;
        break;
      case 'T':
        option.display_tab = 1;
        break;
      default:
        exit(1);
    }
  }
  return option;
}

void file_open(int count, char *argv[], Options option) {
  for (int i = 1; i < count; i++) {
    FILE *f = fopen(argv[i], "r");
    if (f != NULL) {
      int before = '\n';
      int counter = 0;
      int j = 1;
      int c = 0;
      flags(option, before, counter, c, j, f);
      fclose(f);
    }
  }
}

void flags(Options option, int before, int counter, int c, int j, FILE *f) {
  while ((c = fgetc(f)) != EOF) {
    if (option.squeeze_blank) {  // Обработка случая, когда включено сжатие
                                 // пустых строк
      if (c == '\n' && (before == '\n' || before == '\0')) {
        counter++;
      } else {
        counter = 0;
      }
    }
    if (counter <= 1) {
      if (option.number_all_output) {  // Обработка нумерации всех строк
        if ((before == '\n') && !option.number_nonempty) {
          printf("%6d\t", j);
          j++;
        }
      }
      if (option.number_nonempty) {  // Обработка нумерации непустых строк
        if (before == '\n' && c != '\n') {
          printf("%6d\t", j);
          j++;
        }
      }
      if (option
              .end_characters) {  // Обработка отображения символов конца строки
        if (c == '\n') {
          printf("$");
        }
      }
      if (option.display_tab) {  // Обработка отображения символов табуляции
        if (c == '\t') {
          printf("^");
          c = 'I';
        }
      }
      if (option.v) {  // Обработка отображения специальных символов для
                       // значений расширенной таблицы ASCII
        if (c > 127 && c < 160) printf("M-^");
        if ((c < 32 && c != '\n' && c != '\t') || c == 127) printf("^");
        if ((c < 32 || (c > 126 && c < 160)) && c != '\n' && c != '\t')
          c = c > 126 ? c - 128 + 64 : c + 64;
      }
      printf("%c", c);
      before = c;
    }
  }
}