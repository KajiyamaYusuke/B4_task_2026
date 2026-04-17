#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

#define N 100

// ==================== CSV読み込み（行列） ====================
MatrixXd read_matrix(const string &filename) {
    MatrixXd A(N, N);
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "ファイルが開けません: " << filename << endl;
        exit(1);
    }

    string line;
    int i = 0;

    while (getline(file, line) && i < N) {
        stringstream ss(line);
        string value;
        int j = 0;

        while (getline(ss, value, ',') && j < N) {
            A(i, j) = stod(value);
            j++;
        }
        i++;
    }

    return A;
}

// ==================== CSV書き込み ====================
void write_matrix(const string &filename, const MatrixXd &X) {
    ofstream file(filename);

    for (int i = 0; i < X.rows(); i++) {
        for (int j = 0; j < X.cols(); j++) {
            file << X(i, j);
            if (j < X.cols() - 1) file << ",";
        }
        file << "\n";
    }
}

// ==================== メイン ====================
int main() {

    // 入力ディレクトリ
    string base = "/home/takahara/B4_task_2026-1/input/";

    // ファイルパス
    string file1 = base + "matrix1.csv";
    string file2 = base + "matrix2.csv";

    // 読み込み
    MatrixXd M1 = read_matrix(file1);
    MatrixXd M2 = read_matrix(file2);

    // 行列を拡張して Ax=b の形にする（最後の列をbとする）
    MatrixXd A1 = M1.leftCols(N);
    VectorXd b1 = M1.col(N-1);

    MatrixXd A2 = M2.leftCols(N);
    VectorXd b2 = M2.col(N-1);

    // 解く（LU分解）
    VectorXd x1 = A1.colPivHouseholderQr().solve(b1);
    VectorXd x2 = A2.colPivHouseholderQr().solve(b2);

    // 出力
    write_matrix("result1.csv", x1);
    write_matrix("result2.csv", x2);

    cout << "Eigenで計算完了" << endl;

    return 0;
}