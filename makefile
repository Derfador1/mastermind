
CFLAGS+=-g -std=c11 -Wall -Wextra -pedantic -Wno-deprecated -Wstack-usage=1024

practice: mastermind.c
	gcc -o mastermind mastermind.c -lm

debug: CFLAGS+=-g
debug: mastermind

