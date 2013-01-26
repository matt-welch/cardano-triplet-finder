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
int main(int argc, char* argv[]) {
    int a,b,n, count=0 ;
    double numer, denom, c;   
    double term1,exp1,test1,test2,eps ;   
    eps = 1e-11;
    exp1=1.0/3.0;
    n=atoi(argv[1]);
    for(a = 1 ; a < n ; a++)   {   
#ifdef PARALLEL
#pragma omp parallel for shared(count) 
#endif
        for(b = 1 ; b < n ; b++)   {   
            /* Solve for c, determine if it is an integer */
            numer = ((a+1) * (a+1)) * (8*a - 1); 
            denom = 27 * b * b;
            c = (double)numer / (double)denom;
          //  printf ("%i %i %f\n",a,b,c);
            
           
            if(c > 0 && ((c - (int)c)) < eps){
                /* if c is an integer, we've found a triplet */
                if( (a + b + c ) < n ) {
                    /* verify a + b + c < n  (limit)*/ 
                    count++;
                    printf ("%i %i %i\n",a,b,(int)c);
                }
            }
#if 0
            for(c = 1 ; c < n ; c++)   {   
                if (a+b+c<n) {
                    term1=(double)b*sqrt((double)c);
                    test1=(double)a-term1;
                    test2=(double)a+term1;
                if (test1>0) {
                	if (fabs(pow(test2,exp1)+pow(test1,exp1)-1.0)<eps) {
                	    count++;
                	    printf ("%i %i %i\n",a,b,c);
                	}
                } else 
                    {
                    /* branch testing if:::::: */
                    if (fabs(pow(test2,exp1)-pow(-test1,exp1)-1.0)<eps)
                        {
                            count++;
                	        printf ("%i %i %i\n",a,b,c);
                	    }
                    }
                }
            }

#endif
        }
    }   
    printf("Total = %d \n", count) ;   
    return 0;
}   
