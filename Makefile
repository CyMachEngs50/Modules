CFLAGS: -Wall-pedantic-std=c11-|.-g


all:  queuetest hash_test

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

queuetest: queuetest.o queue.o
	gcc $(CFLAGS) queuetest.o queue.o -o $@

hash_test: hash_test.o hash.o
	gcc $(CFLAGS) hash_test.o hash.o -o $@

clean:
	rm -f *.o queuetest 
