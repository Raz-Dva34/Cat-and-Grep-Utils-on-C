#include "s21_grep.h"

int main(int argc, char *argv[]) {
  if (argc > 2) {
    char buff[2000] = "\0";
    char rez[1024] = "\0";
    int countfile = 0;
    char pat_e[MAX_PATTERNS][MAX_PATTERN_LENGTH] = {0};
    regex_t regex = {0};
    t_options options = {0};
    parcer(argc, argv, &options, buff, pat_e);
    reader(argc, argv, buff, rez, countfile, &options, regex);
  } else
    return 0;
}

void parcer(int argc, char *argv[], t_options *options, char *buff,
            char pat_e[MAX_PATTERNS][MAX_PATTERN_LENGTH]) {
  int opt = 0;
  while ((opt = getopt_long(argc, argv, "e:ivclnhsf:o", 0, 0)) != -1) {
    if (argc <= 1) {
      fprintf(stderr, "usage: [options]");
      exit(EXIT_SUCCESS);
    } else {
      switch (opt) {
        case 'e':
          options->e = true;
          flage(buff);
          break;
        case 'i':
          options->i = true;
          break;
        case 'v':
          options->v = true;
          break;
        case 'c':
          options->c = true;
          break;
        case 'l':
          options->l = true;
          break;
        case 'n':
          options->n = true;
          break;
        case 'h':
          options->h = true;
          break;
        case 's':
          options->s = true;
          break;
        case 'f':
          options->f = true;
          flagf(optarg, pat_e, MAX_PATTERNS);
          break;
        case 'o':
          options->o = true;
          break;
        default:
          break;
      }
    }
  }
  if (options->f && options->e) options->e = false;
  if (options->v) options->o = false;
  if (options->c || options->l) {
    options->n = false;
    options->o = false;
  }
  if (options->f) {
    buff[0] = '\0';
    for (int i = 0; i < MAX_PATTERNS && pat_e[i][0] != '\0'; i++) {
      if (i > 0) strcat(buff, "|");
      strcat(buff, pat_e[i]);
    }
  }
}

void reader(int argc, char *argv[], char *buff, char *rez, int countfile,
            t_options *options, regex_t regex) {
  char *pattern = (options->e || options->f) ? buff : argv[optind++];
  int cflags = REG_EXTENDED;
  if (options->i) cflags |= REG_ICASE;
  if (options->v) cflags |= REG_NOMATCH;
  countfile = argc - optind;
  regcomp(&regex, pattern, cflags);
  if (options->o) {
    flago(argc, argv, buff, options, regex, countfile);
    ;
  } else {
    funkcii(argc, argv, rez, countfile, options, regex);
  }
}

void print_line(char *argv[], int file_index, int countfile, t_options *options,
                int countn, char *rez) {
  if (!options->h && countfile > 1) {
    printf("%s:", argv[file_index]);
  }
  if (options->n) {
    printf("%d:", countn);
  }
  printf("%s", rez);
  if (rez[strlen(rez) - 1] != '\n') {
    printf("\n");
  }
}

void funkcii(int argc, char *argv[], char *rez, int countfile,
             t_options *options, regex_t regex) {
  regmatch_t pmatch[1] = {0};
  FILE *f = NULL;
  int countn = 0;
  int countc = 0;
  int counts = 0;
  int regcount = 0;
  for (int i = optind; i < argc; i++) {
    if (argv[i][0] != '-') {
      if ((f = fopen(argv[i], "r")) != NULL) {
        while (fgets(rez, VOLUME, f) != NULL) {
          countn++;
          regcount = regexec(&regex, rez, 1, pmatch, 0);
          if ((options->v && regcount != 0) || (!options->v && regcount == 0)) {
            if (!options->c && !options->l) {
              print_line(argv, i, countfile, options, countn, rez);
            }
            countc++;
          }
        }
        if (options->c) {
          if (!options->h && countfile > 1) printf("%s:", argv[i]);
          printf("%d\n", countc);
        }
        if (options->l && countc > 0) {
          printf("%s\n", argv[i]);
        }
        fclose(f);
        countc = 0;
        countn = 0;
      } else if (f == NULL) {
        counts++;
        if (!options->s && counts > 1) {
          fprintf(stderr, "grep: %s: No such file or directory\n", argv[i]);
        }
      }
    }
  }
  regfree(&regex);
}

void flago(int argc, char *argv[], char *buff, t_options *options,
           regex_t regex, int countfile) {
  regmatch_t pmatch[1] = {0};
  FILE *f = NULL;
  int regcounto = 0;
  int stringcountn = 0;
  int last_printed_line = -1;
  for (int i = optind; i < argc; i++) {
    if (argv[i][0] != '-') {
      if ((f = fopen(argv[i], "r")) != NULL) {
        stringcountn = 0;
        while ((fgets(buff, 2000, f)) != NULL) {
          stringcountn++;
          char *buff_ptr = buff;
          while ((regcounto = regexec(&regex, buff_ptr, 1, pmatch, 0)) == 0) {
            if (countfile > 1 && !options->h) {
              printf("%s:", argv[i]);
            }
            if (options->n && last_printed_line != stringcountn) {
              printf("%d:", stringcountn);
              last_printed_line = stringcountn;
            }
            for (int j = pmatch[0].rm_so; j < pmatch[0].rm_eo; ++j) {
              printf("%c", buff_ptr[j]);
            }
            printf("\n");
            buff_ptr += pmatch[0].rm_eo;
          }
        }
        fclose(f);
      }
    }
  }
  regfree(&regex);
}

void flagf(char *filename, char pat_e[MAX_PATTERNS][MAX_PATTERN_LENGTH],
           int max_patterns) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Unable to open file: %s\n", filename);
    return;
  }
  char line[MAX_PATTERN_LENGTH];
  int pattern_index = 0;
  while (fgets(line, MAX_PATTERN_LENGTH, f) != NULL &&
         pattern_index < max_patterns) {
    line[strcspn(line, "\n")] = 0;
    strncpy(pat_e[pattern_index], line, MAX_PATTERN_LENGTH);
    pattern_index++;
    if (pattern_index < max_patterns) {
      pat_e[pattern_index][0] = '\0';
    }
  }
  fclose(f);
}

void flage(char *buff) {
  if (*buff != '\0') {
    strcat(buff, "|");
  }
  strcat(buff, optarg);
}
