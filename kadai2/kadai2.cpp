#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

// read 2d matrix from csv file : A
vector<vector<double>> readMatrix(const string& filename) {
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
    return matrix;
}

// read 1d vector from csv file : b
vector<double> readVector(const string& filename) {
    ifstream file(filename);
    string line;
    vector<double> vector;
    while (getline(file, line)) {
        vector.push_back(stod(line));
    }
    return vector;
}

// make augmented matrix : [A | b]
vector<vector<double>> makeAugmentedMatrix(vector<vector<double>>& A, const vector<double>& b) {
    vector<vector<double>> augmentedMatrix = A;
    for (int i = 0; i < A.size(); i++) {
        augmentedMatrix[i].push_back(b[i]);
    }
    return augmentedMatrix;
}

// solve equation : Ax = b
vector<double> solveEquation(vector<vector<double>>& augmentedMatrix) {
    int N = augmentedMatrix.size();
    for (int i = 0; i < N; i++) {
        // pivot selection
        if (augmentedMatrix[i][i] == 0) {
            for (int j = i + 1; j < N; j++) {
                if (augmentedMatrix[j][i] != 0) {
                    swap(augmentedMatrix[i], augmentedMatrix[j]);
                    break;
                }
            }
        }
        // elimination
        for (int j = i + 1; j < N; j++) {
            double factor = augmentedMatrix[j][i] / augmentedMatrix[i][i];
            for (int k = i; k < N + 1; k++) {
                augmentedMatrix[j][k] -= factor * augmentedMatrix[i][k];
            }
        }
    }
    // backward substitution
    vector<double> x(N);
    for (int i = N - 1; i >= 0; i--) {
        x[i] = augmentedMatrix[i][N];

        for (int j = i + 1; j < N; j++) {
            x[i] -= augmentedMatrix[i][j] * x[j];
        }
        x[i] /= augmentedMatrix[i][i];
    }
    return x;
}

// export vector to csv file
void exportVector(const vector<double>& x, const string& filename) {
    ofstream file(filename);
    for (int i = 0; i < x.size(); i++) {
        file << x[i] << endl;
    }
    file.close();
}

int main() {
    const string out = "kadai2/kadai2_output.csv";

    // solve equation for matrix1.csv and vector1.csv
    vector<vector<double>> A1 = readMatrix("input/matrix1.csv");
    vector<double> b1 = readVector("input/vector1.csv");
    vector<vector<double>> augmentedMatrix1 = makeAugmentedMatrix(A1, b1);
    vector<double> x1 = solveEquation(augmentedMatrix1);
    exportVector(x1, out);

    return 0;
}