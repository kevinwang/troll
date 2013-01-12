CFLAGS = -Wall -O2 -g -trigraphs -Wno-trigraphs
TROLL_CMDS = help.o init.o face.o

troll: troll.c $(TROLL_CMDS) path.o
path.o: path.h

clean:
	rm -f *.o troll *~

.PHONY: clean
