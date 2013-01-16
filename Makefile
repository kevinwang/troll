CFLAGS = -Wall -O2 -g
TROLL_CMDS = help.o init.o

troll: troll.c $(TROLL_CMDS) face.o path.o
face.o:
	$(CC) $(CFLAGS) -trigraphs -Wno-trigraphs -c -o face.o face.c
path.o: path.h

test: test.c path.o

clean:
	rm -f *.o troll *~

.PHONY: clean
