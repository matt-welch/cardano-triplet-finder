/*******************************************************************************
 * FILENAME:    cardano_triplets.c
 * DESCRIPTION: Cardano Triplet Finder 
 * AUTHOR:      James Matthew Welch [JMW]
 * SCHOOL:      Arizona State University
 * CLASS:       CSE598: High Performance Computing
 * INSTRUCTOR:  Dr. Gil Speyer
 * SECTION:     20520
 * TERM:        Spring 2013
 *******************************************************************************/

# include <stdio.h>  
# include <stdlib.h>
# include <math.h>   
# include <omp.h>
# include <time.h>
# include <sys/time.h>
int main(int argc, char* argv[]) {
    /* numc variables */
    int a,b,n, count=0 ;
    double numer, denom, c;   
    double eps;
    
    /* timing variables */
    struct timeval start, end;
    long seconds, useconds;
    double preciseTime;

    /* Get start time */
    gettimeofday(&start, NULL);

    eps = 1e-11;
    n=atoi(argv[1]);
    for(a = 1 ; a < n ; a++)   {  
        numer = ((a+1) * (a+1)) * (8*a - 1); 
#ifdef PARALLEL
#pragma omp parallel for reduction(+:count) private(b, denom, c) firstprivate(n, a, eps, numer) 
#endif
        /* limit b-values to n-a since a+b+c <= n */
        for(b = 1 ; b < n-a ; b++)   {   
            /* Solve for c, determine if it is an integer */
            denom = 27 * b * b;
            c = (double)numer / (double)denom;
#ifdef VERBOSE
            printf ("%i %i %f\n",a,b,c);
#endif            
            if(c > 0 && ((c - (int)c)) < eps){
                /* if c is an integer, we've found a triplet */
                if( (a + b + c ) <= n ) {
                    /* verify a + b + c < n  (limit)*/ 
                    count++;
#ifndef QUIET
                    printf ("%i %i %i\n",a,b,(int)c);
#endif
                }
            }
       }
/* end parallel for */
    }   
    printf("Total = %d \n", count) ; 
    gettimeofday(&end, NULL);
    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;
    preciseTime = seconds + useconds/1000000.0;
    printf("Total Time = %3.4f\n", preciseTime );  
    return 0;
}   
