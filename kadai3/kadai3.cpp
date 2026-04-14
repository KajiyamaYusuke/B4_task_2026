#include <Eigen/Dense>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// read 2d matrix from csv file : A
Eigen::MatrixXd readMatrix(const string& filename) {
    ifstream file(filename);
    string line;
    vector<vector<double>> matrix;
    while (getline(file, line)) {
        vector<double> row;
        stringstream ss(line);
        string cell;
        while (getline(ss, cell, ',')) {
            row.push_back(stod(cell));
        }
        matrix.push_back(row);
    }
    const Eigen::Index n = static_cast<Eigen::Index>(matrix.size());
    Eigen::MatrixXd A(n, n);
    for (Eigen::Index i = 0; i < n; ++i) {
        for (Eigen::Index j = 0; j < n; ++j) {
            A(i, j) = matrix[static_cast<size_t>(i)][static_cast<size_t>(j)];
        }
    }
    return A;
}

// read 1d vector from csv file : b
Eigen::VectorXd readVector(const string& filename) {
    ifstream file(filename);
    string line;
    vector<double> vector;
    while (getline(file, line)) {
        vector.push_back(stod(line));
    }
    const Eigen::Index n = static_cast<Eigen::Index>(vector.size());
    Eigen::VectorXd b(n);
    for (Eigen::Index i = 0; i < n; ++i) {
        b(i) = vector[static_cast<size_t>(i)];
    }
    return b;
}

// export vector to csv file
void exportVector(const Eigen::VectorXd& x, const string& filename) {
    ofstream file(filename);
    for (Eigen::Index i = 0; i < x.size(); ++i) {
        file << x(i) << endl;
    }
    file.close();
}

int main() {
    const string out = "kadai3/kadai3_output.csv";

    Eigen::MatrixXd A = readMatrix("input/matrix1.csv");
    Eigen::VectorXd b = readVector("input/vector1.csv");
    Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);
    exportVector(x, out);

    return 0;
}
