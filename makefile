CMPLR = $(shell which clang >/dev/null; echo $$?)
ifeq "$(CMPLR)" "0"
CC = clang
else
CC = gcc
endif
CFLAGS = -O3 -pedantic -Wall -Wextra
TG = test

%: test.c tweetfips202_%.o
	$(CC) $(CFLAGS) -DPITHY_VER=$@ -o $(TG)$@ $^

tweetfips202_%.o: %t/tweetfips202.c
	$(CC) $(CFLAGS) -c $^ -o $@

all: 9 8 7

.PHONY: clean style

clean:
	rm -f *.o $(TG)?

style:
	astyle -z2 *.c *.h

