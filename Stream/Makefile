CC=gcc
AS=as
LD=ld
AR=ar
GF=f77

CFLAGS= -Wall -lm
FFLAGS= -Wall 

all: stream-x86-c stream-x86-f stream2-x86-f stream2-x86-c derived

stream-x86-c: Stream.c
	$(CC) -O -fopenmp -o stream-x86-c Stream.c $(CFLAGS)

stream-x86-c-tiny: Stream.c
	$(CC) -O -DSTREAM_ARRAY_SIZE=10000 -DNTIMES=2 -fopenmp -o stream-x86-c-tiny Stream.c $(CFLAGS)

stream-x86-c-small: Stream.c
	$(CC) -O -DSTREAM_ARRAY_SIZE=1000000 -DNTIMES=2 -fopenmp -o stream-x86-c-small Stream.c $(CFLAGS)

derivation: derivation.c
	$(CC) -O -fopenmp -o derivation derivation.c $(CFLAGS)

stream2-x86-c: Stream2.c 
	$(CC) -O -o stream2-x86-c Stream2.c $(CFLAGS) 	

stream-x86-f: Stream.f mysecond.c
	$(CC) -c mysecond.c
	$(GF) -O Stream.f mysecond.o -o stream-x86-f $(FFLAGS)
	
stream2-x86-f: Stream2.f mysecond.c
	$(CC) -c mysecond.c
	$(GF) -O Stream2.f mysecond.o -o stream2-x86-f $(FFLAGS)		
	
	
clean:
	rm -f *.o *-c *-f fort.3
