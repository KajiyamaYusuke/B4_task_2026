#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

vector<vector<double>> readMatrixA(const string& filename) {
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
    return A;
}

vector<double> readVectorb(const string& filename) {
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
    return b; }


vector<double> Gauss(vector<vector<double>> A, vector<double> b) {
    int n = A.size();

    for (int i=0; i<n; i++) {
        // pivot selection
        int maxRow = i;
        double maxVal = abs(A[i][i]);
        for (int j=i+1; j<n; j++) {
            if (abs(A[j][i]) > maxVal) {
                maxVal = abs(A[j][i]);
                maxRow = j;
            }
        }
        swap(A[i], A[maxRow]);
        swap(b[i], b[maxRow]);

        if (abs(A[i][i]) < 1e-15) {
            throw runtime_error("A is singular");
        }

        // forward elimination
        for (int j=i+1; j<n; j++) {
            double factor = A[j][i] / A[i][i];
            b[j] -= factor * b[i];
            for (int k=i; k<n; k++) {
                A[j][k] -= factor * A[i][k];
            }
        }
    }

    // backward substitution
    vector<double> x(n);
    for (int i=n-1; i>=0; i--) {
        double sum = 0;
        for (int j=i+1; j<n; j++) {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i]-sum)  / A[i][i];
    }
    return x;
}


void exportVector(const vector<double>& x, const string& filename) {
    ofstream file(filename);
    if(!file.is_open()) {
        throw runtime_error("Could not open "+ filename);
    }

    file << fixed << setprecision(10);
    for (const auto& val : x) {
        file << val << "\n";
    }
}

int main() {
    try {
        string matrixA = "input/matrix1.csv";
        string vectorb = "input/vector1.csv";
        string outputx = "kadai2_output.csv";

        vector<vector<double>> A = readMatrixA(matrixA);
        vector<double> b = readVectorb(vectorb);

        vector<double> x = Gauss(A, b);

        exportVector(x, outputx);

    } catch (const exception& e) {
        cerr << "Exception:" << e.what() << endl;
        return 1;
    }
    return 0;
}