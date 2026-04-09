#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <Eigen/Dense>

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

void saveCSV(std::string filename, const std::vector<double>& result) {
std::ofstream file(filename);
for (double val : result) {
    file << val << "\n"; 
    } 
}

void EigenSolve(std::string mPath, std::string vPath, std::string outPath) {
    auto A_vec = readCSV(mPath);
    auto b_vec = readCSV(vPath);
    int rows = A_vec.size();
    int cols = A_vec[0].size();
    Eigen::MatrixXd A(rows, cols);
    for (int i = 0; i < rows; i++) 
        for (int j = 0; j < cols; j++) 
            A(i, j) = A_vec[i][j];
    Eigen::VectorXd b(rows);
        for (int i = 0; i < rows; i++)
            b(i) = b_vec[i][0];
    Eigen::VectorXd x = A.colPivHouseholderQr().solve(b);
    std::vector<double> result(x.data(), x.data() + x.size());
    saveCSV(outPath, result);
    std::cout << "Eigen solved[" << mPath << "] -> " << outPath << std::endl;
}

int main() {
    EigenSolve("input/matrix1.csv", "input/vector1.csv", "P3output1.csv");
    EigenSolve("input/matrix2.csv", "input/vector2.csv", "P3output2.csv");
    return 0;
}