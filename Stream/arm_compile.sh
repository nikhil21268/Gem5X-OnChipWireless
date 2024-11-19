gcc -O -DSTREAM_ARRAY_SIZE=5000000 -DNTIMES=3 -DTUNED -fopenmp -o stream-arm-c Stream.c -Wall -lm -static 
gcc -O -DSTREAM_ARRAY_SIZE=2000000 -DNTIMES=2 -DTUNED -DDELAY=1000 -fopenmp -o stream-delay-arm-c Stream_delay.c -Wall -lm -static
gcc -O -DSTREAM_ARRAY_SIZE=85330 -DNTIMES=10 -DTUNED -D_GNU_SOURCE -DNCORES=16 -fopenmp -o stream-ic-arm-c Stream_ic.c -Wall -lm -static 
gcc -O -fopenmp -o stream2-arm-c Stream2.c -Wall -lm -static
