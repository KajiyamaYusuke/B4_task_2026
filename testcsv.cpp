#include <iostream>
#include <vector>
#include <fstream>
#include <random>

using namespace std;

const int N = 100;

// CSV書き出し（行列）
void writeMatrix(const string& filename, const vector<vector<double>>& mat) {
    ofstream file(filename);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            file << mat[i][j];
            if (j != N - 1) file << ",";
        }
        file << endl;
    }
}

// CSV書き出し（ベクトル）
void writeVector(const string& filename, const vector<double>& vec) {
    ofstream file(filename);
    for (int i = 0; i < N; i++) {
        file << vec[i] << endl;
    }
}

int main() {
    vector<vector<double>> A(N, vector<double>(N));
    vector<double> x(N);  // 真の解
    vector<double> b(N);

    // 乱数生成（再現性あり）
    mt19937 gen(0);
    uniform_real_distribution<> dist(-10.0, 10.0);

    // 行列 A を生成
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i][j] = dist(gen);
        }
    }

    // 真の解 x を生成
    for (int i = 0; i < N; i++) {
        x[i] = dist(gen);
    }

    // b = A x を計算
    for (int i = 0; i < N; i++) {
        b[i] = 0.0;
        for (int j = 0; j < N; j++) {
            b[i] += A[i][j] * x[j];
        }
    }

    // CSV出力
    writeMatrix("matrix1.csv", A);
    writeVector("vector1.csv", b);
    writeVector("true_x.csv", x);  // 正解も保存！

    cout << "テストデータ生成完了！" << endl;
    cout << "matrix1.csv, vector1.csv, true_x.csv を出力しました。" << endl;

    return 0;
}