#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

const int N = 100;

// ===== CSV読み込み =====
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

// ===== ノルム計算 =====
double calcErrorNorm(const vector<double>& a, const vector<double>& b) {
    double sum = 0.0;
    for (int i = 0; i < N; i++) {
        sum += pow(a[i] - b[i], 2);
    }
    return sqrt(sum);
}

// ===== 残差計算 =====
double calcResidual(const vector<vector<double>>& A, const vector<double>& x, const vector<double>& b) {
    double sum = 0.0;

    for (int i = 0; i < N; i++) {
        double Ax = 0.0;
        for (int j = 0; j < N; j++) {
            Ax += A[i][j] * x[j];
        }
        sum += pow(Ax - b[i], 2);
    }

    return sqrt(sum);
}

// ===== メイン =====
int main() {
    // ファイル読み込み
    vector<vector<double>> A = readMatrix("matrix1.csv");
    vector<double> b = readVector("vector1.csv");
    vector<double> x_calc = readVector("result.csv");
    vector<double> x_true = readVector("true_x.csv");

    // 誤差
    double error = calcErrorNorm(x_calc, x_true);

    // 残差
    double residual = calcResidual(A, x_calc, b);

    // 出力
    cout << "=== 誤差評価 ===" << endl;
    cout << "解の誤差 ||x_calc - x_true|| = " << error << endl;
    cout << "残差     ||Ax - b||        = " << residual << endl;

    return 0;
}