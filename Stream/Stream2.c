/************************************************
* Program:  STREAM2                             *
* Revision: 0.1, 99.10.26                       *
* Author:   John McCalpin                       *
*           john@mccalpin.com                   *
*************************************************
*-----------------------------------------------------------------------
* Copyright 1991-2003: John D. McCalpin
*-----------------------------------------------------------------------
* License:
*  1. You are free to use this program and/or to redistribute
*     this program.
*  2. You are free to modify this program for your own use,
*     including commercial use, subject to the publication
*     restrictions in item 3.
*  3. You are free to publish results obtained from running this
*     program, or from works that you derive from this program,
*     with the following limitations:
*     3a. In order to be referred to as "STREAM2 benchmark results",
*         published results must be in conformance to the STREAM
*         Run Rules, (briefly reviewed below) published at
*         http://www.cs.virginia.edu/stream/ref.html
*         and incorporated herein by reference.
*         As the copyright holder, John McCalpin retains the
*         right to determine conformity with the Run Rules.
*     3b. Results based on modified source code or on runs not in
*         accordance with the STREAM Run Rules must be clearly
*         labelled whenever they are published.  Examples of
*         proper labelling include:
*         "tuned STREAM2 benchmark results" 
*         "based on a variant of the STREAM2 benchmark code"
*         Other comparable, clear and reasonable labelling is
*         acceptable.
*     3c. Submission of results to the STREAM benchmark web site
*         is encouraged, but not required.
*  4. Use of this program or creation of derived works based on this
*     program constitutes acceptance of these licensing restrictions.
*  5. Absolutely no warranty is expressed or implied.
*-----------------------------------------------------------------------
*************************************************
* This program measures sustained bandwidth     *
* using four computational kernels:             *
*                                               *
*       FILL:   a(i) = 0                        *
*       COPY:   a(i) = b(i)                     *
*       DAXPY:  a(i) = a(i) + q*b(i)            *
*       DOT:    sum += a(i) * b(i)              *
*                                               *
* Results are presented in MB/s, assuming       *
*   8 Bytes per iteration for FILL,             *
*  16 Bytes per iteration for COPY & DOT, and   *
*  24 Bytes per iteration for DAXPY             *
************************************************/

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <float.h>
# include <limits.h>
# include <sys/time.h>

#ifdef NTIMES
#if NTIMES<=1
#   define NTIMES	10
#endif
#endif
#ifndef NTIMES
#   define NTIMES	10
#endif

#ifndef NMIN
#   define NMIN	30
#endif

#ifndef NMAX
#   define NMAX 2000000
#endif

#ifndef NUMSIZES
#   define NUMSIZES	32
#endif

#ifndef NPAD
#   define NPAD	0
#endif

#ifndef STREAM_TYPE
#define STREAM_TYPE double
#endif

#ifndef MEGA
#define MEGA 1000000
#endif

#ifndef GIGA
#define GIGA 1000000000
#endif

#ifndef STREAM_TYPE
#define STREAM_TYPE double
#endif


# ifndef MIN
# define MIN(x,y) ((x)<(y)?(x):(y))
# endif
# ifndef MAX
# define MAX(x,y) ((x)>(y)?(x):(y))
# endif
#ifndef abs
#define abs(a) ((a) >= 0 ? (a) : -(a))
#endif

extern double mysecond();




#ifdef _OPENMP
extern int omp_get_num_threads();
#endif
int main()
{
	printf("\nSTREAM2 Running\n");
		
	static STREAM_TYPE	a[NMAX+NPAD], b[NMAX+NPAD];
	
	printf("------------");
	printf("------------");
	printf("------------");
	printf("------------");
	printf("------------");
	printf("------------\n");
	
	double			times[4][NTIMES];
	STREAM_TYPE		scalar;
	STREAM_TYPE		sum0, sum1, sum2, sum3;
	STREAM_TYPE		sum4, sum5, sum6, sum7;
	STREAM_TYPE		sum, start, finish;
	STREAM_TYPE		exp, tdelta;
	
	STREAM_TYPE		rate[4], besttime[4], bytes[4];
	
	int				i, j, k, l, M, inner;
	int 			alltimes = 1;
	int 			tab = 0;
	
	
	// bytes initialisation 
	bytes[0]	= 8;
	bytes[1]	= 16;
	bytes[2]	= 24;
	bytes[3]	= 16;
	


    // check timer granularity
	
	for(i=0;i<MIN(10000,NMAX);i++)
	{
		a[i] = 0;
	}
	
	for(i=0;i<MIN(10000,NMAX);i++)
	{
		a[i] = mysecond();
	}
	tdelta = 1.36;
	
	for(i=0;i<(MIN(10000,NMAX)-1);i++)
	{
		if (a[i+1] != a[i])
		{	
			tdelta = MIN(tdelta, abs(a[i+1]-a[i]));
		}
	}
	tdelta*=GIGA;
	
	
	
	printf("Smallest time delta is %0.3lf nano seconds\n\n", tdelta);
	printf("     Size  Iter      FILL         COPY        DAXPY       DOT\n\n");
	// Loop over problem size
	
	system("m5 checkpoint");
	
	for(j=1;j<=NUMSIZES;j++) // ------ main loop ------ //
	{
		//printf(" %d iteration \n", j);
		
		exp = log10((double)NMIN) 
			+ ((double)(j-1))/((double)(NUMSIZES-1))
			* (log10((double)NMAX)-log10((double)NMIN));	
		//printf("exp is %0.20lf \n", exp);
			
			
	    M = floor(pow(10,exp));  
		//printf("M is %ld \n", M);
		
		
	    for(i=0;i<M;i++) // ------- initialize arrays ------ //
		{
	        a[i] = 0;
	        b[i] = 0;
			//printf("1.1 : i = %d \n", i);
	    }


	    for(k=0;k<NTIMES;k++) // ------ do NTIMES times the eperience ------- //
		{
			inner = NMAX/M;
			
			start = mysecond();  // ------ FILL --------
			#pragma omp parallel for
			for(l=0;l<inner;l++)
			{
				
	            scalar = (double)(k+l);
	            for(i=1;i<M;i++)
				{
	    	        a[i] = scalar;
					
					//printf("l is %d \n", l); 
	            }
	        }
	        finish = mysecond();
	        times[0][k] = (finish-start)/((double)inner);
			
			
			//printf("%0.20lf  ", times[1][k]); 			
			
			
	        start = mysecond();
			#pragma omp parallel for
			for(l=0;l<inner;l++)  // ------ COPY ------
			{
				a[l] = 1;
				for(i=1;i<M;i++)
				{
					b[i] = a[i];
				}
			}
			finish = mysecond();
			times[1][k] = (finish-start)/((double)inner);   

			
			start = mysecond();	
			#pragma omp parallel for
			for(l=0;l<inner;l++)    // -------- DAXPY ------
			{
				a[l] = 1;
				for(i=1;i<M;i++)
				{
					b[i] = b[i] + scalar*a[i];
				}
			}
			finish = mysecond();
			times[2][k] = (finish-start)/((double)inner);
			
			
			start = mysecond();
			#pragma omp parallel for
			for(l=0;l<inner;l++)   // ------ DOT -----
			{
				b[l] = 1;
				sum0 = 0;
				sum1 = 0;
				sum2 = 0;
				sum3 = 0;
				sum4 = 0;
				sum5 = 0;
				sum6 = 0;
				sum7 = 0;
				for(i=1;i<M;i=i+8)
				{	
					sum0 = sum0 + a[i+0]*b[i+0];
					sum1 = sum1 + a[i+1]*b[i+1];
					sum2 = sum2 + a[i+2]*b[i+2];
					sum3 = sum3 + a[i+3]*b[i+3];
					sum4 = sum4 + a[i+4]*b[i+4];
					sum5 = sum5 + a[i+5]*b[i+5];
					sum6 = sum6 + a[i+6]*b[i+6];
					sum7 = sum7 + a[i+7]*b[i+7];
				}
			}
			sum = sum0 + sum1 + sum2 
				+ sum3 + sum4 + sum5 
				+ sum6 + sum7;
			finish = mysecond();
			times[3][k] = (finish-start)/((double)inner);
		}
		
		
		
		tab=ceil(log10(M));
		for(k=0;k<9-tab;tab++){printf(" ");}
        printf("%d   %d", M, NTIMES);
		
	    for(i=0;i<4;i++) // loop 1.3
		{
			besttime[i] = GIGA;
	        for(k=0;k<NTIMES;k++)
			{
				if((besttime[i]-times[i][k]) > 0){besttime[i]=times[i][k];}
				
	            //besttime[i] = (double)MIN(besttime[i],times[i][k]);
				//printf("times    %0.3lf \n", times[i][k]);
				//printf("besttime %0.3lf \n", besttime[i]);
				
				//if (alltimes){printf("%d %d %d %lf\n", M, i, k, times[i][k]);}
				//besttime[i]*=10^9;
	        }
	        rate[i] = ((double)M) * bytes[i]/besttime[i];
			//rate[i] = ((double)M) * 64/besttime[i];
			//printf(" rate is %lf\n", rate[i]);
			//rate[i] = rate[i]/MEGA;
			//printf(" rate is %0.0lf", rate[i]);
			//printf("    %f    ", besttime[i]);
			tab=ceil(log10(rate[i]/MEGA));
			for(k=0;k<10-tab;tab++){printf(" ");}
			printf("%0.1lf", rate[i]/MEGA);
			
			
			//printf("    %0.1lf  ", rate[i]/MEGA);
			
		}
		//printf("------changement size---------\n\n");
		printf("\n");
	}
	system("m5 exit");
	return 0;
}



double mysecond()
{
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}



