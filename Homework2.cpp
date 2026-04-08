#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

// 行列を読み込み
vector<vector<double>> readCSV(string filename) {
    vector<vector<double>> data;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        vector<double> row;
        stringstream ss(line);
        string val;
        while (getline(ss, val, ',')) {
            row.push_back(stod(val));
        }
        data.push_back(row);
    }
    return data;
}

//  Ax = b 
vector<double> solveLinearEquation(vector<vector<double>> A, vector<double> b) {
    int n = A.size();

    // 前進消去
    for (int i = 0; i < n; i++) {
        double pivot = A[i][i];
        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / pivot;
            for (int k = i; k < n; k++) {
                A[j][k] -= factor * A[i][k];
            }
            b[j] -= factor * b[i];
        }
    }

    // 後退代入
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += A[i][j] * x[j];
        }
        x[i] = (b[i] - sum) / A[i][i];
    }
    return x;
}

int main() {
    // 1. データの読み込み
    auto matrix = readCSV("/workspace/B4_task_2026/input/matrix1.csv");
    auto vector_data = readCSV("/workspace/B4_task_2026/input/vector1.csv");
    
    // vector1.csv が縦ベクトル (1列) の場合を想定して変換
    vector<double> b;
    for(auto& row : vector_data) b.push_back(row[0]);

    // 2. 計算実行
    vector<double> x = solveLinearEquation(matrix, b);

    // 3. 結果をCSVに出力
    ofstream outfile("output.csv");
    for (double val : x) {
        outfile << fixed << setprecision(10) << val << "\n";
    }
    outfile.close();

    cout << "計算が完了しました。output.csv を確認してください。" << endl;
    return 0;
}