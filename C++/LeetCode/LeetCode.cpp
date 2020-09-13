/*
力扣算法与数据结构练习
 */
#include<iostream>
#include "map"
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

    int romanToInt(string s) {
        int result = 0;
        map<char,int> map_test = {
                {'I',1},
                {'V',5},
                {'X',10},
                {'L',50},
                {'C',100},
                {'D',500},
                {'M',1000}
        };
        for(int i=0;i<s.length();i++){
            if (map_test[s[i]]>=map_test[s[i+1]]){
                result += map_test[s[i]];
            }else{
                result -= map_test[s[i]];
            }
        }
        return result;
    }
};

int main(){
    Solution solution;
/*
 * 罗马数字转阿拉伯数字***************************
 */
//    int i = solution.romanToInt("III");
//    std::cout << i;
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

