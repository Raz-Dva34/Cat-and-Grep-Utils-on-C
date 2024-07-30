# Simple Bash Utils

Development of Bash utilities for working with text: cat, grep.

## The program is developed in the C language of the C11 standard using the gcc compiler.
## The program assembly is configured using Makefile with the corresponding targets: s21_cat, s21_grep.
## There are tests in the same Makefile

## Part 1. Development of the cat utility

cat:
- supports all flags (including GNU versions)

## Part 2. Development of the grep utility

grep:
- Support for the following flags: `-e`, `-i`, `-v`, `-c`, `-l`, `-n`
- For regular expressions, only pcre or regex libraries can be used
- Support for all flags, including: `-h`, `-s`, `-f`, `-o`
- Support for all flags, including their _paired_ combinations (e.g. `-iv`, `-in`)

cat is one of the most commonly used commands in Unix-like operating systems. The command has three interrelated functions regarding text files: displaying, merging their copies, and creating new ones.

`cat [OPTION] [FILE]...`

### cat Options

| # | Options | Description |
| ------ | ------ | ------ |
| 1 | -b (GNU: --number-nonblank) | numbers only nonblank lines |
| 2 | -e assumes -v (GNU only: -E is the same but does not use -v) | also displays newlines as $ |
| 3 | -n (GNU: --number) | numbers all output lines |
| 4 | -s (GNU: --squeeze-blank) | squeezes multiple adjacent blank lines |
| 5 | -t assumes -v (GNU: -T is the same but does not use -v) | also displays tabs as ^I |

grep - Thompson wrote the first version in PDP-11 assembly language to help Lee E. McMahon analyze the text of The Federalist Papers and determine the authorship of individual articles. The text editor ed (also created by Thompson) had support for regular expressions, but it couldn't be used for such a large amount of text, so Thompson extracted the code into a separate tool. He chose the name because in ed the g / re / p command would print all lines that matched a given pattern.
grep was first included in Version 4 Unix. Stating that it is "commonly cited as the prototype of a software tool", McIlroy credited grep with "irrevocably introducing" Thompson's tool philosophy into Unix.

### Using grep

`grep [options] template [file_name]`

### Options for grep

| # | Options | Description |
| ------ | ------ | ------ |
| 1 | -e | The pattern. |
| 2 | -i | Ignore case distinctions. |
| 3 | -v | Invert the meaning of the match search. |
| 4 | -c | Print only the number of matching lines. |
| 5 | -l | Print only the matching files. |
| 6 | -n | Prepend each output line with the line number from the input file. |
| 7 | -h | Print the matching lines without prepending the file names. |
| 8 | -s | Suppress error messages about nonexistent or unreadable files. |
| 9 | -f file | Get regular expressions from a file. |
| 10 | -o | Print only the matching (non-empty) parts of the matched line. |
