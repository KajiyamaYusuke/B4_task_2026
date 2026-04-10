#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

//ファイルの読み込みを行いEigen Matrixに変換
MatrixXd read_csv(const string& filename){
    ifstream file(filename);
    string line;
    vector<vector<double>> matrix_data;

    while (getline(file, line))
    {
        //cout <<"読み込んだ行："<< line<<endl;
        stringstream ss(line);
        string val;

        vector<double> row;

        while (getline(ss, val, ','))
        {
           //cout << "要素 [" << val <<"]" << endl;
           row.push_back(stod(val));
        }

        matrix_data.push_back(row);
        

    }
    int i, j ;
    int rows = matrix_data.size();
    int cols = matrix_data[0].size();
/*行列の取得ができているのかの確認
    for(i=0 ; i < rows ; i ++){
        for(j=0 ; j < cols ; j++){
        cout << matrix_data[i][j] << " ";
        if (j == cols-1){
            cout  << endl;
        }
        }
     }
*/ 
    MatrixXd A(rows, cols);
    for(i=0 ; i < rows ; i ++){
        for(j=0 ; j < cols ; j++){
            A(i, j) = matrix_data[i][j];
        }
     }
    // cout << A <<endl;
    return A;
}



//メイン
int main (){
    string filename_for_matrix = "input/matrix1.csv";
    string filename_for_vector = "input/vector1.csv";

    //データの読み込み
    MatrixXd A = read_csv(filename_for_matrix);
    //m行1列の行列b_row
    MatrixXd b_row = read_csv(filename_for_vector);
    //m次元のベクトルに変換
    VectorXd b = b_row.col(0);
    //cout << b << endl;

    //Ax = bの解を求める関数
    VectorXd x = A.colPivHouseholderQr().solve(b);
    //cout << x << endl;

    //結果の出力
    ofstream outfile("result3");

        for(int i = 0; i < x.size(); i++){
            outfile << x(i) << endl;
        }
    
    outfile.close();
    return 0;
}