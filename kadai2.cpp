#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;

void SolveAndSave(string matlixfile, string vectorFile, string outputFile){
     int N = 100;

     vector<vector<double>> A(N,vector<double>(N));
     vector<double> b(N);

     ifstream fileA(matrixFile), fileB(vectorFile);

}

     char comma;

     for (int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            fileA >> A[i][j];
            if (j < N-1) fileA >> comma;
        }
        fileB >> b[i];
     }
    
     

