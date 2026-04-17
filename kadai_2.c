#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100

// ==================== CSV読み込み（行列） ====================
void read_matrix(const char *filename, double A[N][N]) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("ファイル %s が開けません\n", filename);
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(fp, "%lf", &A[i][j]);
            if (j < N - 1) fscanf(fp, ",");
        }
    }

    fclose(fp);
}

// ==================== CSV読み込み（ベクトル） ====================
void read_vector(const char *filename, double b[N]) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("ファイル %s が開けません\n", filename);
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        fscanf(fp, "%lf", &b[i]);
    }

    fclose(fp);
}

// ==================== CSV書き込み ====================
void write_vector(const char *filename, double x[N]) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("ファイル %s が開けません\n", filename);
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        fprintf(fp, "%lf\n", x[i]);
    }

    fclose(fp);
}

// ==================== LU分解（部分ピボット） ====================
void lu_decomposition(double A[N][N], int pivot[N]) {
    for (int i = 0; i < N; i++) pivot[i] = i;

    for (int k = 0; k < N; k++) {

        // ピボット選択
        int max = k;
        for (int i = k + 1; i < N; i++) {
            if (fabs(A[i][k]) > fabs(A[max][k])) {
                max = i;
            }
        }

        // 行交換
        if (max != k) {
            for (int j = 0; j < N; j++) {
                double tmp = A[k][j];
                A[k][j] = A[max][j];
                A[max][j] = tmp;
            }
            int tmp = pivot[k];
            pivot[k] = pivot[max];
            pivot[max] = tmp;
        }

        // LU分解
        for (int i = k + 1; i < N; i++) {
            A[i][k] /= A[k][k];
            for (int j = k + 1; j < N; j++) {
                A[i][j] -= A[i][k] * A[k][j];
            }
        }
    }
}

// ==================== 前進代入 ====================
void forward_substitution(double A[N][N], double b[N], double y[N], int pivot[N]) {
    double bp[N];

    // ピボット適用
    for (int i = 0; i < N; i++) {
        bp[i] = b[pivot[i]];
    }

    for (int i = 0; i < N; i++) {
        y[i] = bp[i];
        for (int j = 0; j < i; j++) {
            y[i] -= A[i][j] * y[j];
        }
    }
}

// ==================== 後退代入 ====================
void backward_substitution(double A[N][N], double y[N], double x[N]) {
    for (int i = N - 1; i >= 0; i--) {
        x[i] = y[i];
        for (int j = i + 1; j < N; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}

// ==================== メイン ====================
int main() {

    double A1[N][N], A2[N][N];
    double b1[N], b2[N];
    double x1[N], x2[N];
    double y[N];
    int pivot[N];

    // ===== 入力パス（指定ディレクトリ） =====
    const char *base = "/home/takahara/B4_task_2026-1/input/";

    char m1[256], m2[256], v1[256], v2[256];

    sprintf(m1, "%smatrix1.csv", base);
    sprintf(m2, "%smatrix2.csv", base);
    sprintf(v1, "%svector1.csv", base);
    sprintf(v2, "%svector2.csv", base);

    // ===== 読み込み =====
    read_matrix(m1, A1);
    read_matrix(m2, A2);
    read_vector(v1, b1);
    read_vector(v2, b2);

    // ===== 1つ目 =====
    lu_decomposition(A1, pivot);
    forward_substitution(A1, b1, y, pivot);
    backward_substitution(A1, y, x1);

    // ===== 2つ目 =====
    lu_decomposition(A2, pivot);
    forward_substitution(A2, b2, y, pivot);
    backward_substitution(A2, y, x2);

    // ===== 出力 =====
    write_vector("result1.csv", x1);
    write_vector("result2.csv", x2);

    printf("計算完了（LU分解）\n");

    return 0;
}