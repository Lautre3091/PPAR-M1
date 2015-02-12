
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>

int main (int argc, char *argv[]){

    struct timeval start, end;
    int* tab;
    int n, i,j, max_prime_n;
    time_t time;

    //setup starting time
    gettimeofday(&start,0);

    //setup a table from 0 to n
    n = atoi(argv[1]);
    tab=(int*) malloc(n*sizeof(int));
    for(i=0;i<n;i++){
        tab[i]=1;
    }

    //calculate boundary of the for loop
    max_prime_n = (int)sqrt(n);

    //Fork a team of threads giving them their own copies of variables
#pragma omp parallel
    {
        //look for prime numbers from 2 to sqrt(n)
        for(i=2;i<max_prime_n;i++){
            j=i;
            //eliminate the multiples of i
            while(j<n){
                j+=i;
                tab[j]=0;
            }
            i++;
        }
    }
    //calculate computation time
    gettimeofday(&end,0);
    time= (time_t)(end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
    printf("execution time:%d\n",(int) time);

    //display prime numbers
    printf("prime numbers up to %d:\n",n);
    for(i=2;i<n;i++){
        if(tab[i]==1)printf("%d\n", i);
    }
    return 0;
}
