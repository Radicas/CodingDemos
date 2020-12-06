#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& A) {
        int row = A.size();
        int column = A[0].size();
        vector<vector<int>> B(column);
        for (int i=0;i<B.size();i++){
            B[i].resize(row);
        }
        for (int i=0;i<A.size();i++){
            for (int j=0;j<A[i].size();j++){
                B[j][i] = A[i][j];
            }
        }
        for (int i=0;i<B.size();i++){
            for (int j=0;j<B[i].size();j++){
                cout << B[i][j];
            }
            cout << endl;
        }

    }
};

int main(){
    Solution solution;

    /*
     * 翻转数组，将二维数组下标互换*********************************
     */
//    int num = 1;
//    vector<vector<int>> A(3);
//    for (int i=0;i<A.size();i++){
//        A[i].resize(3);
//    }
//    for (int i=0;i<A.size();i++) {
//        for (int j = 0; j < A[i].size(); j++) {
//            A[i][j] = num;
//            num++;
//        }
//    }
//    solution.transpose(A);
}


