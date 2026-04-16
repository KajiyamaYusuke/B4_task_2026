#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <Eigen/Dense>
#include <stdexcept>

using namespace std;
using namespace Eigen;

MatrixXd readMatrixA(const string& filename) {
    ifstream file(filename);
    if(!file.is_open()) {
        throw runtime_error("Could not open "+ filename);
    }

    vector<vector<double>> A;
    string line;
    while (getline(file, line)) {
        vector<double> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            if (!cell.empty()) {
                row.push_back(stod(cell));
            }
        }
        if(!row.empty()) {
            A.push_back(row);
        }
    }
    int Rows = A.size();

    if (A.empty()) {
        throw runtime_error("Matrix file is empty");
    }

    int Columns = A[0].size();

    for (int i = 0; i < Rows; i++) {
        if (A[i].size() != Columns) {
            throw runtime_error("Inconsistent column size in matrix");
        }
    }

    MatrixXd matrix(Rows, Columns);
    for (int i=0; i<Rows; i++) {
        for (int j=0; j<Columns; j++) {
            matrix(i,j) = A[i][j];
        }
    }

    return matrix;    
}

VectorXd readVectorb(const string& filename) {
    ifstream file(filename);
    if(!file.is_open()) {
        throw runtime_error("Could not open "+ filename);
    }

    vector<double> b;
    string cell;
    while (getline(file, cell)) {
        if(!cell.empty()) {
            b.push_back(stod(cell));
        }
    }

    int n = b.size();
    VectorXd vector(n);
    for (int i=0; i<n; i++) {
        vector(i) = b[i];
    }

    return vector;
}

void exportVector(const VectorXd& x, const string& filename) {
    ofstream file(filename);
    if(!file.is_open()) {
        throw runtime_error("Could not open "+ filename);
    }

    file << fixed << setprecision(10);
    for (int i=0; i<x.size(); i++) {
        file << x(i) << "\n";
    }
}

int main() {
    try {
        string matrixA = "input/matrix1.csv";
        string vectorb = "input/vector1.csv";
        string outputx = "kadai3_output.csv";

        MatrixXd A = readMatrixA(matrixA);
        VectorXd b = readVectorb(vectorb);

        if (A.rows() != b.size()) {
            throw runtime_error("Size mismatch");
        }

        VectorXd x = A.colPivHouseholderQr().solve(b);

        exportVector(x, outputx);

    } catch (const exception& e) {
        cerr << "Exception:" << e.what() << endl;
        return 1;
    }
    return 0;
}