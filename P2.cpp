#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip> 
#include <cmath> 

std::vector<std::vector<double>> readCSV(std::string filename) {
    std::vector<std::vector<double>> data;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return data;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        std::vector<double> row;
        std::stringstream ss(line);
        std::string value;
        while (std::getline(ss, value, ',')) {
            try {
                row.push_back(std::stod(value));
            } catch (...) { continue; }
        }
        if (!row.empty()) data.push_back(row);
    }
    return data;
}

std::vector<double> solveLinearSystem(std::vector<std::vector<double>> A, std::vector<double> b) {
    int n = b.size();
    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (std::abs(A[k][i]) > std::abs(A[maxRow][i])) {maxRow = k; }
        }
        std::swap(A[i], A[maxRow]);
        std::swap(b[i], b[maxRow]);
        
        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            b[k] -= factor * b[i];
            for (int j = i; j < n; j++) {
                A[k][j] -= factor * A[i][j];
            }
        }
    }
    std:: vector <double> x(n);
    for (int i = n -1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) sum += A[i][j] * x[j];
        x[i] = (b[i] - sum) / A[i][i];
    }
    return x;
}

void saveCSV(std::string filename, const std::vector<double>& result) {
std::ofstream file(filename);
for (double val : result) {
    file << val << "\n"; 
    } 
}

void processSystem(std::string mPath, std::string vPath, std::string outPath) {
    std::vector<std::vector<double>> A = readCSV(mPath);
    std::vector<std::vector<double>> b_raw = readCSV(vPath);
     if (A.empty() || b_raw.empty()) {
        return;
     }

     std::vector<double> b;
     for(auto& row : b_raw) b.push_back(row[0]);

     std::vector<double> x = solveLinearSystem(A, b);
     saveCSV(outPath, x);
     std::cout << "System [" << mPath << "] solved -> " << outPath << std::endl;
}

int main() {
    processSystem("input/matrix1.csv", "input/vector1.csv", "P2output1.csv");
    processSystem("input/matrix2.csv", "input/vector2.csv", "P2output2.csv");
    std::cout << "\nAll P2 systems processed successfully!" << std::endl;
    return 0;
}