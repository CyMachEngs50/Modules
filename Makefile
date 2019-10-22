CFLAGS: -Wall-pedantic-std=c11 -g -ggdb


all: listTest  queuetest hash_test listTest

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

queuetest: queuetest.o queue.o
	gcc $(CFLAGS) queuetest.o queue.o -o $@

hash_test: hash_test.o hash.o
	gcc $(CFLAGS) hash_test.o hash.o -o $@

listTest: listTest.o list.o
	gcc $(CFLAGS) listTest.o list.o -o $@

clean:
	rm -f *.o queuetest hash_test listTest
