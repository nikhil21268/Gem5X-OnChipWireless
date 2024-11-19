/*-----------------------------------------------------------------------*/
/* Program: STREAM                                                       */
/* Revision: $Id: stream.c,v 5.10 2013/01/17 16:01:06 mccalpin Exp mccalpin $ */
/* Original code developed by John D. McCalpin                           */
/* Programmers: John D. McCalpin                                         */
/*              Joe R. Zagar                                             */
/*                                                                       */
/* This program measures memory transfer rates in MB/s for simple        */
/* computational kernels coded in C.                                     */
/*-----------------------------------------------------------------------*/
/* Copyright 1991-2013: John D. McCalpin                                 */
/*-----------------------------------------------------------------------*/
/* License:                                                              */
/*  1. You are free to use this program and/or to redistribute           */
/*     this program.                                                     */
/*  2. You are free to modify this program for your own use,             */
/*     including commercial use, subject to the publication              */
/*     restrictions in item 3.                                           */
/*  3. You are free to publish results obtained from running this        */
/*     program, or from works that you derive from this program,         */
/*     with the following limitations:                                   */
/*     3a. In order to be referred to as "STREAM benchmark results",     */
/*         published results must be in conformance to the STREAM        */
/*         Run Rules, (briefly reviewed below) published at              */
/*         http://www.cs.virginia.edu/stream/ref.html                    */
/*         and incorporated herein by reference.                         */
/*         As the copyright holder, John McCalpin retains the            */
/*         right to determine conformity with the Run Rules.             */
/*     3b. Results based on modified source code or on runs not in       */
/*         accordance with the STREAM Run Rules must be clearly          */
/*         labelled whenever they are published.  Examples of            */
/*         proper labelling include:                                     */
/*           "tuned STREAM benchmark results"                            */
/*           "based on a variant of the STREAM benchmark code"           */
/*         Other comparable, clear, and reasonable labelling is          */
/*         acceptable.                                                   */
/*     3c. Submission of results to the STREAM benchmark web site        */
/*         is encouraged, but not required.                              */
/*  4. Use of this program or creation of derived works based on this    */
/*     program constitutes acceptance of these licensing restrictions.   */
/*  5. Absolutely no warranty is expressed or implied.                   */
/*-----------------------------------------------------------------------*/
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <float.h>
# include <limits.h>
# include <sys/time.h>

/*-----------------------------------------------------------------------
 * INSTRUCTIONS:
 *
 *	1) STREAM requires different amounts of memory to run on different
 *           systems, depending on both the system cache size(s) and the
 *           granularity of the system timer.
 *     You should adjust the value of 'STREAM_ARRAY_SIZE' (below)
 *           to meet *both* of the following criteria:
 *       (a) Each array must be at least 4 times the size of the
 *           available cache memory. I don't worry about the difference
 *           between 10^6 and 2^20, so in practice the minimum array size
 *           is about 3.8 times the cache size.
 *           Example 1: One Xeon E3 with 8 MB L3 cache
 *               STREAM_ARRAY_SIZE should be >= 4 million, giving
 *               an array size of 30.5 MB and a total memory requirement
 *               of 91.5 MB.  
 *           Example 2: Two Xeon E5's with 20 MB L3 cache each (using OpenMP)
 *               STREAM_ARRAY_SIZE should be >= 20 million, giving
 *               an array size of 153 MB and a total memory requirement
 *               of 458 MB.  
 *       (b) The size should be large enough so that the 'timing calibration'
 *           output by the program is at least 20 clock-ticks.  
 *           Example: most versions of Windows have a 10 millisecond timer
 *               granularity.  20 "ticks" at 10 ms/tic is 200 milliseconds.
 *               If the chip is capable of 10 GB/s, it moves 2 GB in 200 msec.
 *               This means the each array must be at least 1 GB, or 128M elements.
 *
 *      Version 5.10 increases the default array size from 2 million
 *          elements to 10 million elements in response to the increasing
 *          size of L3 caches.  The new default size is large enough for caches
 *          up to 20 MB. 
 *      Version 5.10 changes the loop index variables from "register int"
 *          to "ssize_t", which allows array indices >2^32 (4 billion)
 *          on properly configured 64-bit systems.  Additional compiler options
 *          (such as "-mcmodel=medium") may be required for large memory runs.
 *
 *      Array size can be set at compile time without modifying the source
 *          code for the (many) compilers that support preprocessor definitions
 *          on the compile line.  E.g.,
 *                gcc -O -DSTREAM_ARRAY_SIZE=100000000 stream.c -o stream.100M
 *          will override the default size of 10M with a new size of 100M elements
 *          per array.
 */
#ifndef STREAM_ARRAY_SIZE
#   define STREAM_ARRAY_SIZE	8000000
#endif


# define HLINE "-------------------------------------------------------------\n"

# ifndef MIN
# define MIN(x,y) ((x)<(y)?(x):(y))
# endif
# ifndef MAX
# define MAX(x,y) ((x)>(y)?(x):(y))
# endif

#ifndef STREAM_TYPE
#define STREAM_TYPE double
#endif

static STREAM_TYPE	a[STREAM_ARRAY_SIZE];

#ifdef _OPENMP
extern int omp_get_num_threads();
#endif

int main()
{
    int			BytesPerWord;
    int			k;
    ssize_t		j;
    double		sum;

    /* --- SETUP --- determine precision and check timing --- */

    BytesPerWord = sizeof(STREAM_TYPE);
    printf("This system uses %d bytes per array element.\n",
	BytesPerWord);

    printf(HLINE);

    printf("Array size = %llu (elements)\n" , (unsigned long long) STREAM_ARRAY_SIZE);
    printf("Memory per array = %.1f MiB (= %.1f GiB).\n", 
	BytesPerWord * ( (double) STREAM_ARRAY_SIZE / 1024.0/1024.0),
	BytesPerWord * ( (double) STREAM_ARRAY_SIZE / 1024.0/1024.0/1024.0));

#ifdef _OPENMP
    printf(HLINE);
#pragma omp parallel 
    {
#pragma omp master
	    {
	    k = omp_get_num_threads();
	    printf ("Number of Threads requested = %i\n",k);
        }
    }
#endif

#ifdef _OPENMP
	k = 0;
#pragma omp parallel
#pragma omp atomic 
		k++;
    printf ("Number of Threads counted = %i\n",k);
#endif

//storing initial values
#pragma omp parallel for
    for (j=0; j<STREAM_ARRAY_SIZE; j+=8) {
	    a[j] = 1.0;
	}

    printf(HLINE);
//summing over all values	
	sum = 0.0;
    system("m5 checkpoint");
#pragma omp parallel for
    for (j = 0; j < STREAM_ARRAY_SIZE; j+=8)
		a[j] = 2.0* a[j];
    printf("sum = %f\n", sum);
    system("m5 exit");
    printf("first value in array is = %f\n", a[0]);
    printf("last adjusted value in array is = %f\n", a[STREAM_ARRAY_SIZE - STREAM_ARRAY_SIZE % 8 - 8]);

return 0;
}
   
    
   
