#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

const int N = 100;

// 行列CSV読み込み
bool readMatrixCSV(const string& filename, MatrixXd& A) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error: cannot open " << filename << endl;
        return false;
    }

    A.resize(N, N);
    string line;
    int row = 0;

    while (getline(fin, line) && row < N) {
        stringstream ss(line);
        string cell;
        int col = 0;

        while (getline(ss, cell, ',') && col < N) {
            A(row, col) = stod(cell);
            col++;
        }

        if (col != N) {
            cerr << "Error: invalid column count in " << filename
                 << " at row " << row + 1 << endl;
            return false;
        }

        row++;
    }

    if (row != N) {
        cerr << "Error: invalid row count in " << filename << endl;
        return false;
    }

    return true;
}

// ベクトルCSV読み込み
bool readVectorCSV(const string& filename, VectorXd& b) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error: cannot open " << filename << endl;
        return false;
    }

    b.resize(N);
    string line;
    int row = 0;

    while (getline(fin, line) && row < N) {
        if (line.empty()) {
            cerr << "Error: empty line in " << filename
                 << " at row " << row + 1 << endl;
            return false;
        }

        b(row) = stod(line);
        row++;
    }

    if (row != N) {
        cerr << "Error: invalid row count in " << filename << endl;
        return false;
    }

    return true;
}

// ベクトルCSV出力
bool writeVectorCSV(const string& filename, const VectorXd& x) {
    ofstream fout(filename);
    if (!fout) {
        cerr << "Error: cannot open " << filename << " for writing" << endl;
        return false;
    }

    for (int i = 0; i < x.size(); i++) {
        fout << x(i) << endl;
    }

    return true;
}

int main() {
    MatrixXd A;
    VectorXd b;

    if (!readMatrixCSV("input/matrix1.csv", A)) {
        return 1;
    }

    if (!readVectorCSV("input/vector1.csv", b)) {
        return 1;
    }

    // 連立方程式 Ax = b を解く
    VectorXd x = A.colPivHouseholderQr().solve(b);

    // 検算用残差
    VectorXd r = A * x - b;
    cout << "Residual norm = " << r.norm() << endl;

    if (!writeVectorCSV("answer.csv", x)) {
        return 1;
    }

    cout << "Solution was written to answer.csv" << endl;
    return 0;
}