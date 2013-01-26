/*******************************************************************************
 * FILENAME:    cardano_triplets.c
 * DESCRIPTION: 
 * AUTHOR:      James Matthew Welch [JMW]
 * SCHOOL:      Arizona State University
 * CLASS:       CSE598: High Performance Computing
 * INSTRUCTOR:  Dr. Gil Speyer
 * SECTION:     
 * TERM:        Spring 2013
 *******************************************************************************/

# include <stdio.h>  
# include <stdlib.h>
# include <math.h>   
# include <omp.h>
# include <time.h>
#include <sys/time.h>
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

#if 0
    double term1,exp1,test1,test2;   
    exp1=1.0/3.0;
#endif
    eps = 1e-11;
    n=atoi(argv[1]);
    for(a = 1 ; a < n ; a++)   {   
#ifdef PARALLEL
#pragma omp parallel for reduction(+:count) private(b, numer, denom, c) firstprivate(n, a, eps)
#endif
        for(b = 1 ; b < n ; b++)   {   
            /* Solve for c, determine if it is an integer */
            numer = ((a+1) * (a+1)) * (8*a - 1); 
            denom = 27 * b * b;
            c = (double)numer / (double)denom;
#ifdef DEBUG
            printf ("%i %i %f\n",a,b,c);
#endif            
           
            if(c > 0 && ((c - (int)c)) < eps){
                /* if c is an integer, we've found a triplet */
                if( (a + b + c ) <= n ) {
                    /* verify a + b + c < n  (limit)*/ 
                    count++;
                    printf ("%i %i %i\n",a,b,(int)c);
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
