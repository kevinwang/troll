CFLAGS = -Wall -O2 -g -Wno-unused-result
LDFLAGS = -lcrypto
TROLL_CMDS = help.o init.o add.o ls-files.o cmd-commit.o log.o status.o checkout.o

troll: troll.c $(TROLL_CMDS) face.o path.o object.o blob.o index.o tree.o commit.o
	$(CC) -o troll $(CFLAGS) $^ $(LDFLAGS)
face.o:
	$(CC) $(CFLAGS) -trigraphs -Wno-trigraphs -c -o face.o face.c
path.o: path.h
object.o: object.h
blob.o: blob.h
tree.o: tree.h
status.o: index.h
commit.o: commit.h
checkout.o: checkout.h

test: test.c object.o path.o index.o tree.o commit.o
	$(CC) -o test $(CFLAGS) $^ $(LDFLAGS)

clean:
	rm -f *.o troll *~ test

.PHONY: clean
