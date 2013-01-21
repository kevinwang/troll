CFLAGS = -Wall -O2 -g
TROLL_CMDS = help.o init.o

troll: troll.c $(TROLL_CMDS) face.o path.o object.o
face.o:
	$(CC) $(CFLAGS) -trigraphs -Wno-trigraphs -c -o face.o face.c
path.o: path.h
object.o: object.c object.h
	$(CC) $(CFLAGS) -Wno-format-contains-nul -c -o object.o object.c

test: test.c object.o

clean:
	rm -f *.o troll *~ test

.PHONY: clean
