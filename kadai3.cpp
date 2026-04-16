#include <iostream>
#include <fstream>
#include <string>
#include <Eigen/Dense> 

using namespace std;
using namespace Eigen;

void solveWithEigen(string matrixFile, string vectorFile, string outputFile) {
    int N = 100;
    
    MatrixXd A(N, N);
    VectorXd b(N);

    ifstream fileA(matrixFile), fileB(vectorFile);
    if (!fileA || !fileB) {
        cerr << "エラー: ファイルが開けません (" << matrixFile << ", " << vectorFile << ")" << endl;
        return;
    }

    char comma;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fileA >> A(i, j); 
            if (j < N - 1) fileA >> comma;
        }
        fileB >> b(i);
    }

    VectorXd x = A.partialPivLu().solve(b);

    // 4. CSVへの書き出し
    ofstream outFile(outputFile);
    for (int i = 0; i < N; i++) {
        outFile << x(i) << "\n";
    }

    cout << "処理完了: " << outputFile << " に結果を出力しました。" << endl;
}

int main() {
    cout << "Eigenを使った課題3の計算を開始します..." << endl;

    solveWithEigen("input/matrix1.csv", "input/vector1.csv", "output3.csv");

    cout << "すべての処理が完了しました。" << endl;
    return 0;
}