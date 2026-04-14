#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

const int N = 100;

// CSV読み込み（行列）
vector<vector<double>> readMatrix(const string& filename) {
    vector<vector<double>> mat(N, vector<double>(N));
    ifstream file(filename);
    string line;

    int i = 0;
    while (getline(file, line) && i < N) {
        stringstream ss(line);
        string value;
        int j = 0;

        while (getline(ss, value, ',') && j < N) {
            mat[i][j] = stod(value);
            j++;
        }
        i++;
    }
    return mat;
}

// CSV読み込み（ベクトル）
vector<double> readVector(const string& filename) {
    vector<double> vec(N);
    ifstream file(filename);
    string line;

    int i = 0;
    while (getline(file, line) && i < N) {
        vec[i] = stod(line);
        i++;
    }
    return vec;
}

// CSV書き出し
void writeVector(const string& filename, const vector<double>& vec) {
    ofstream file(filename);
    for (int i = 0; i < N; i++) {
        file << vec[i] << endl;
    }
}

// ガウス消去法（部分ピボット）
vector<double> gaussianElimination(vector<vector<double>> A, vector<double> b) {
    for (int i = 0; i < N; i++) {

        // ピボット選択
        int maxRow = i;
        for (int k = i + 1; k < N; k++) {
            if (abs(A[k][i]) > abs(A[maxRow][i])) {
                maxRow = k;
            }
        }

        // 行交換
        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);

        // 前進消去
        for (int k = i + 1; k < N; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < N; j++) {
                A[k][j] -= factor * A[i][j];
            }
            b[k] -= factor * b[i];
        }
    }

    // 後退代入
    vector<double> x(N);
    for (int i = N - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < N; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }

    return x;
}

int main() {
    // ファイル名（必要に応じて変更）
    string matrixFile = "input/matrix1.csv";
    string vectorFile = "input/vector1.csv";

    // 読み込み
    vector<vector<double>> A = readMatrix(matrixFile);
    vector<double> b = readVector(vectorFile);

    // 解く
    vector<double> x = gaussianElimination(A, b);

    // 書き出し
    writeVector("result.csv", x);

    cout << "計算完了。result.csv に出力しました。" << endl;

    return 0;
}