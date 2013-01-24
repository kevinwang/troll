CFLAGS = -Wall -O2 -g
LDFLAGS = -lssl
TROLL_CMDS = help.o init.o add.o

troll: troll.c $(TROLL_CMDS) face.o path.o object.o blob.o
face.o:
	$(CC) $(CFLAGS) -trigraphs -Wno-trigraphs -c -o face.o face.c
path.o: path.h
object.o: object.h
blob.o: blob.h

test: test.c object.o path.o

clean:
	rm -f *.o troll *~ test

.PHONY: clean
