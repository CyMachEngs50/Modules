CFLAGS: -Wall-pedantic-std=c11-|.-g


all:  queuetest 

%.o: %.c %.h
	gcc $(CFLAGS) -c $<

queuetest: queuetest.o queue.o
	gcc $(CFLAGS) queuetest.o queue.o -o $@


clean:
	rm -f *.o queuetest 
