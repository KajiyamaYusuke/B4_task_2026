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
            } catch (...) {
                continue; 
            }
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
            if (std::abs(A[k][i]) > std::abs(A[maxRow][i])) {
                maxRow = k;
            }
        }
        std::swap(A[i], A[maxRow]);
        std::swap(b[i], b[maxRow]);
        
        for (int k = i + 1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            b[k] -= factor * b[i];
            for (int j = i; j <n; j++) {
                A[k][j] = factor *A[i][j];
            }
        }
    }
    std:: vector <double> x(n);
    for (int i = n -1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += A[i][j] * x[j];
        }
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

int main() {
    std::string matrixPath = "input/matrix1.csv";
    std::string vectorPath = "input/vector1.csv";
    
    std::vector<std::vector<double>> A = readCSV(matrixPath);
    std::vector<std::vector<double>> b_raw = readCSV(vectorPath);
     if (A.empty() || b_raw.empty()) {
        return 1;
     }

     std::vector<double> b;
     for(auto& row : b_raw) b.push_back(row[0]);

     std::cout << "Successfully loaded files!" << std::endl;
     std::cout << "Matrix A size:" << A.size() << "x" << A[0].size() << std::endl;
     std::cout << "Vector b size:" << b.size() << std::endl;
     std::cout <<"------------------------------" << std::endl;
     std::cout << "First 3x3 of Matrix A:" <<std::endl;
     for(int i=0; i<3; ++i) {
        for(int j=0; j<3; ++j) {
            std::cout << std::setw(10) << A[i][j] << " ";
        }
        std::cout << "..." << std::endl;
     }

     std::cout << "\nFirst 3 elements of Vector b:" << std::endl;
     for(int i=0; i<3; ++i) {
        std::cout << "b[" << i << "]: " << b[i] << std::endl;
     }
     
     std::vector<double> x1 = solveLinearSystem(A,b);
     saveCSV("output1.csv", x1);
     std::cout << "System solved and results saved to output1.csv" << std::endl;
    
     return 0;
    }

