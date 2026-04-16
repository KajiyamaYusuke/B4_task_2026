#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100
#define EPS 1e-12

int read_matrix_csv(const char *filename, double A[N][N]) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: cannot open %s\n", filename);
        return 0;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (j < N - 1) {
                if (fscanf(fp, "%lf,", &A[i][j]) != 1) {
                    printf("Error: invalid format in %s at row %d col %d\n", filename, i + 1, j + 1);
                    fclose(fp);
                    return 0;
                }
            } else {
                if (fscanf(fp, "%lf", &A[i][j]) != 1) {
                    printf("Error: invalid format in %s at row %d col %d\n", filename, i + 1, j + 1);
                    fclose(fp);
                    return 0;
                }
            }
        }
    }

    fclose(fp);
    return 1;
}

int read_vector_csv(const char *filename, double b[N]) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: cannot open %s\n", filename);
        return 0;
    }

    for (int i = 0; i < N; i++) {
        if (fscanf(fp, "%lf", &b[i]) != 1) {
            printf("Error: invalid format in %s at row %d\n", filename, i + 1);
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);
    return 1;
}

void swap_rows(double A[N][N], double b[N], int r1, int r2) {
    if (r1 == r2) return;

    for (int j = 0; j < N; j++) {
        double temp = A[r1][j];
        A[r1][j] = A[r2][j];
        A[r2][j] = temp;
    }

    double tempb = b[r1];
    b[r1] = b[r2];
    b[r2] = tempb;
}

int gaussian_elimination(double A[N][N], double b[N], double x[N]) {
    for (int k = 0; k < N; k++) {
        int pivot = k;
        double max_val = fabs(A[k][k]);

        for (int i = k + 1; i < N; i++) {
            if (fabs(A[i][k]) > max_val) {
                max_val = fabs(A[i][k]);
                pivot = i;
            }
        }

        if (max_val < EPS) {
            printf("Error: matrix is singular or nearly singular.\n");
            return 0;
        }

        swap_rows(A, b, k, pivot);

        for (int i = k + 1; i < N; i++) {
            double factor = A[i][k] / A[k][k];
            A[i][k] = 0.0;

            for (int j = k + 1; j < N; j++) {
                A[i][j] -= factor * A[k][j];
            }

            b[i] -= factor * b[k];
        }
    }

    for (int i = N - 1; i >= 0; i--) {
        double sum = b[i];
        for (int j = i + 1; j < N; j++) {
            sum -= A[i][j] * x[j];
        }

        if (fabs(A[i][i]) < EPS) {
            printf("Error: zero diagonal element found during back substitution.\n");
            return 0;
        }

        x[i] = sum / A[i][i];
    }

    return 1;
}

int write_vector_csv(const char *filename, double x[N]) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: cannot open %s for writing\n", filename);
        return 0;
    }

    for (int i = 0; i < N; i++) {
        fprintf(fp, "%.15f\n", x[i]);
    }

    fclose(fp);
    return 1;
}

int main(void) {
    double A[N][N];
    double b[N];
    double x[N];

    if (!read_matrix_csv("input/matrix1.csv", A)) {
        return 1;
    }

    if (!read_vector_csv("input/vector1.csv", b)) {
        return 1;
    }

    if (!gaussian_elimination(A, b, x)) {
        return 1;
    }

    if (!write_vector_csv("answer.csv", x)) {
        return 1;
    }

    printf("Solution was written to answer.csv\n");
    return 0;
}