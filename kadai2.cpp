#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

void solveAndSave(string matlixfile, string vectorFile, string outputFile){
     int N = 100;

     vector<vector<double>> A(N,vector<double>(N));
     vector<double> b(N);

     ifstream fileA(matlixfile), fileB(vectorFile);

     char comma;

     for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            fileA >> A[i][j];
            if (j < N-1) fileA >> comma;
        }
        fileB >> b[i];
     }
    
     for (int i = 0; i < N; i++){
        int pivot = i;
        for (int k= i + 1; k < N; k++){
            if (abs(A[k][i]) > abs(A[pivot][i])) pivot = k;
        }
     
     swap(A[i], A[pivot]);
     swap(b[i], b[pivot]);

     for (int k = i + 1; k < N; k++){
        double f = A[k][i] / A[i][i];
        
        for (int j = 1; j < N; j++){
            A[k][j] -= f * A[i][j];
        }
        b[k] -= f * b[i];
     }

    }

    for (int i = N - 1; i >= 0; i--) {
        
        for (int j = i + 1; j < N; j++) { 
            b[i] -= A[i][j] * b[j]; 
        }
        b[i] /= A[i][i]; 
        
    }

    ofstream outFile(outputFile);
    
    for (int i = 0; i < N; i++) {
        outFile << b[i] << "\n"; 
    }

    cout << "処理完了: " << outputFile << " に結果を出力しました。" << endl;
}

int main() {
    cout << "課題2の計算を開始します..." << endl;

    solveAndSave("matrix1.csv", "vector1.csv", "output1.csv");
    
    solveAndSave("matrix2.csv", "vector2.csv", "output2.csv");

    cout << "すべての処理が完了しました。" << endl;
    return 0; 
}