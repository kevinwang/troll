CFLAGS = -Wall -O2
TROLL_CMDS = help.o init.o trollface.o

troll: troll.c $(TROLL_CMDS)

clean:
	rm -f *.o troll

.PHONY: clean
