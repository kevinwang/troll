CFLAGS = -Wall -O2 -g
LDFLAGS = -lcrypto
TROLL_CMDS = help.o init.o add.o ls-files.o

troll: troll.c $(TROLL_CMDS) face.o path.o object.o blob.o index.o tree.o
	$(CC) -o troll $(CFLAGS) $^ $(LDFLAGS)
face.o:
	$(CC) $(CFLAGS) -trigraphs -Wno-trigraphs -c -o face.o face.c
path.o: path.h
object.o: object.h
blob.o: blob.h
tree.o: tree.h

test: test.c object.o path.o index.o tree.o

clean:
	rm -f *.o troll *~ test

.PHONY: clean
