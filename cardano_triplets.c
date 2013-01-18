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
# include <math.h>   
int main(int argc, char* argv[]) {
    int i,j,k,n, count=0 ;   
    double term1,exp1,test1,test2,eps ;   
    eps = 1e-11;
    exp1=1.0/3.0;
    n=atoi(argv[1]);
    for(i = 1 ; i < n ; i++)   {   
        for(j = 1 ; j < n ; j++)   {   
            for(k = 1 ; k < n ; k++)   {   
                if (i+j+k<n) {
                    term1=(double)j*sqrt((double)k);
                    test1=(double)i-term1;
                    test2=(double)i+term1;
                if (test1>0) {
                	if (fabs(pow(test2,exp1)+pow(test1,exp1)-1.0)<eps) {
                	    count++;
                	    printf ("%i %i %i\n",i,j,k);
                	}
                }
                else {
                	    if (fabs(pow(test2,exp1)-pow(-test1,exp1)-1.0)<eps) {
                	        count++;
                	        printf ("%i %i %i\n",i,j,k);
                	    }
                    }
                }
            }
        }
    }   
    printf("Total = %d \n", count) ;   
    return 0;
}   
