CC = gcc
CFLAG = -std=c11 -Wall -Werror -Wextra
EXECUTABLE = s21_grep

ifeq ($(shell uname -s),Darwin)
 TEST_COMMAND = sh test_func_grep.sh
else
 TEST_COMMAND = bash test_func_grep.sh
endif

all: s21_grep

s21_grep: 
	$(CC) $(CFLAG) s21_grep.c -o $(EXECUTABLE)

test:
	$(TEST_COMMAND)

style: 
	clang-format -style=Google -n *.c *.h

clean:
	rm s21_grep

rebuild: clean all