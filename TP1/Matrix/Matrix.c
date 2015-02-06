#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    int n, nthreads, tid, i, j;
    int** matrix1;
    int** matrix2;
    int** matrixR;

    //Get matrix size from parameter
    n = atoi(argv[1]);

    //Memory allocation
    matrix1=(int **) malloc(n*sizeof(int));
    matrix2=(int **) malloc(n*sizeof(int));
    matrixR=(int **) malloc(n*sizeof(int));

    //Populate the matrix with random numbers
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            matrix1[i][j]=rand()%11;
            matrix1[i][j]=rand()%11	;
        }
    }

    //Define the number of threads
    omp_set_num_threads(n);
    //Fork a team of threads giving them their own copies of variables
    #pragma omp parallel private(nthreads, tid)
    {
        tid = omp_get_thread_num();
        //multiply row from matrix1 with column from matrix2
        for(i=0; i<n;i++){
            for(j=0; j<n; j++){
                matrixR[i][tid]+=matrix1[j][i]*matrix2[i][j];
            }
        }
    }
    return 0;
}