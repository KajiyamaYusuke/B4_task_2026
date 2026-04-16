#include <iostream>
#include <fstream>
#include <sstream>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

const int N = 100;

// ===== CSV読み込み（行列）=====
MatrixXd readMatrix(const string& filename) {
    MatrixXd mat(N, N);
    ifstream file(filename);
    string line;

    int i = 0;
    while (getline(file, line) && i < N) {
        stringstream ss(line);
        string value;
        int j = 0;

        while (getline(ss, value, ',') && j < N) {
            mat(i, j) = stod(value);
           // cout << mat(i,j) << endl;
            j++;
        }
        i++;
    }
    return mat;
}

// ===== CSV読み込み（ベクトル）=====
VectorXd readVector(const string& filename) {
    VectorXd vec(N);
    ifstream file(filename);
    string line;

    int i = 0;
    while (getline(file, line) && i < N) {
        vec(i) = stod(line);
        i++;
    }
    return vec;
}

// ===== CSV書き出し =====
void writeVector(const string& filename, const VectorXd& vec) {
    ofstream file(filename);
    for (int i = 0; i < vec.size(); i++) {
        file << vec(i) << endl;
    }
}

// ===== 解く関数 =====
VectorXd solveSystem(const string& matrixFile, const string& vectorFile) {
    MatrixXd A = readMatrix(matrixFile);
    VectorXd b = readVector(vectorFile);

    // Eigenで解く（安定）
    VectorXd x = A.colPivHouseholderQr().solve(b);

    return x;
}

// ===== main =====
int main() {

    // ---- 1つ目のデータ ----
    VectorXd x1 = solveSystem("input/matrix1.csv", "input/vector1.csv");
    writeVector("output/result1.csv", x1);

    // ---- 2つ目のデータ ----
    VectorXd x2 = solveSystem("input/matrix2.csv", "input/vector2.csv");
    writeVector("output/result2.csv", x2);

    cout << "計算完了！ result1.csv, result2.csv を出力しました。" << endl;

    return 0;
}