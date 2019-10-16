CFLAGS: -Wall-pedantic-std=c11-|.-g


all:  queuetest hashtest

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

queuetest: queuetest.o queue.o
	gcc $(CFLAGS) queuetest.o queue.o -o $@

hashtest: hash_test.o hash.o
	gcc $(CFLAGS) hash_test.o hash.o -o $@

clean:
	rm -f *.o queuetest hashtest
