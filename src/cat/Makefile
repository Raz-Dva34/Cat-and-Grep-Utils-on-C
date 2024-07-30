CC = gcc
CFLAG = -std=c11 -Wall -Werror -Wextra
EXECUTABLE = s21_cat

ifeq ($(shell uname -s),Darwin)
 TEST_COMMAND = sh test_func_cat.sh
else
 TEST_COMMAND = bash test_func_cat.sh
endif

all: s21_cat

s21_cat: 
	$(CC) $(CFLAG) s21_cat.c -o $(EXECUTABLE)

test:
	$(TEST_COMMAND)

style: 
	clang-format -style=Google -n *.c *.h

clean:
	rm s21_cat

rebuild: clean all