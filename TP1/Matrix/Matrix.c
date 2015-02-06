
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main (int argc, char *argv[]){

    struct timeval start, end;
    int n, k, i, j;
    time_t temps;
    int** matrix1;
    int** matrix2;
    int** matrixR;

    gettimeofday(&start,0);

    //Get matrix size from parameter
        n = atoi(argv[1]);

    //Memory allocation
    matrix1=(int **) malloc(n*sizeof(int*));
    matrix2=(int **) malloc(n*sizeof(int*));
    matrixR=(int **) malloc(n*sizeof(int*));

    for(i=0; i<n;i++){
        matrix1[i]=(int *) malloc(n*sizeof(int));
        matrix2[i]=(int *) malloc(n*sizeof(int));
        matrixR[i]=(int *) malloc(n*sizeof(int));
    }

    //Populate the matrix with random numbers
    srand((unsigned int) time(NULL));
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            matrix1[i][j]=rand()%11;
            matrix2[i][j]=rand()%11;
        }
    }

    //Fork a team of threads giving them their own copies of variables
#pragma omp parallel for private(k, i, j)
    //multiply row from matrix1 with column from matrix2
    for(i=0; i<n;i++){
        for(j=0; j<n;j++){
            for(k=0; k<n; k++){
                matrixR[i][j]+=matrix1[i][k]*matrix2[k][j];
            }
        }
    }
    // All threads join master thread and disband

    gettimeofday(&end,0);
    temps=(end.tv_sec * 1000000 + end.tv_usec) - (start.tv_sec * 1000000 + start.tv_usec);
    printf("execution time:%d\n",(int)temps);

    return 0;
}