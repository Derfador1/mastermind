CFLAGS+=-g -std=c11 -Wall -Wextra -pedantic -Wno-deprecated -Wstack-usage=1024

mastermind: mastermind.c
	gcc -g -std=c11 -Wall -Wextra -pedantic -Wno-deprecated -Wstack-usage=1024 -o mastermind mastermind.c -lm

debug: CFLAGS+=-g
debug: mastermind


clean:
	-rm mastermind
