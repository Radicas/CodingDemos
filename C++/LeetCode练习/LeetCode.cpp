#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> twoSum(vector<int>& nums, int target) {
        vector<vector<int>> result = {};
        vector<int> tmp = {};
        for (int i=0;i<nums.size();i++){
            for (int j=i+1;j<nums.size();j++){
                if (nums[i]+nums[j]==target){
                    //cout << nums.size();
                    tmp.push_back(i);
                    tmp.push_back(j);
                    result.push_back(tmp);
                }
            }
        }
        return result;
    }

    int reverse(int x) {
        try {
            if (x >= INT_MAX || x <= INT_MIN)
                return 0;
            int num;
            string tmp;
            string returnNum;
            if (x > 0) {
                while (0 != x) {
                    num = x % 10;
                    tmp = to_string(num);
                    returnNum.append(tmp);
                    cout << returnNum << endl;
                    x /= 10;
                }
            } else if (x < 0) {
                returnNum = "-";
                x = -x;
                while (0 != x) {
                    num = x % 10;
                    tmp = to_string(num);
                    returnNum.append(tmp);
                    cout << returnNum << endl;
                    x /= 10;
                }
            } else {
                num = 0;
            }

            return stoi(returnNum);
        } catch (exception e) {
            return 0;
        }
    }

    bool isPalindrome(int x) {
        long int temp = x;
        long int num = 0;
        if (x<0){
            return false;
        }
        while (x!=0){
            num = num*10 + x%10;
            x /= 10;
        }
        if (temp == num){
            cout << "true";
            return true;
        } else{
            cout << "false";
            return false;
        }
    }


};

int main(){
    Solution solution;
/*
 * 判断回文数***********************************
 */
//    int num = 121;
//    solution.isPalindrome(num);
/*
 * 数字倒序，不能溢出int**************************
 */
//    int i = 214748;
//    solution.reverse(i);
/*
 * 加和*****************************************
 */
//    vector<int> nums = {1,2,3,4,5,6,7};
//    int target = 9;
//    solution.twoSum(nums,target);
}

