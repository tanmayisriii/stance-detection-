#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 2048
#define B 4

void init_matrix(int mat[N][N]) {
    srand(time(NULL));
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            mat[i][j] = rand() % 3 - 1;
        }
    }
}

void print_matrix(int mat[N][N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void square_matrix(int mat[N][N], int res[N][N]) {
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            res[i][j] = 0;
        }
    }
    #pragma omp parallel for
    for (int i = 0; i < N; i += B) {
        for (int j = 0; j < N; j += B) {
            for (int k = 0; k < N; k += B) {
                for (int ii = i; ii < i + B; ii++) {
                    for (int jj = j; jj < j + B; jj++) {
                        for (int kk = k; kk < k + B; kk++) {
                            res[ii][jj] += mat[ii][kk] * mat[kk][jj];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int mat[N][N];
    int res[N][N];

    init_matrix(mat);

    square_matrix(mat, res);

    print_matrix(res);

    return 0;
}
