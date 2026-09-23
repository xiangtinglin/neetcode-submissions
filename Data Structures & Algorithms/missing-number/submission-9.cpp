// g++ -std=c++17 -Wall -Wextra -g3 Test.cpp -o output/Test_cpp

# include <iostream>
# include <vector>
#include <sstream>
using namespace std;

class Solution {
public:
    // int missingNumber(vector<int>& nums) {
    //     int n = nums.size();
    //     sort(nums.begin(), nums.end());
    //     for (int i = 0; i < n; i++) {
    //         if (i != nums[i]) {
    //             return i;
    //         }
    //     }
    //     return n;
    // }

    // int missingNumber(vector<int>& nums) {
    //     int n = nums.size();
    //     unordered_set<int> set_nums(nums.begin(), nums.end());
    //     for (int i = 0; i <= n; i++) {
    //         if (set_nums.find(i) == set_nums.end()) {
    //             return i;
    //         }
    //     }
    //     return -999;    // 防呆設計
    // }

    // int missingNumber(vector<int>& nums) {
    //     int n = nums.size();
    //     int xorr = n;
    //     for (int i = 0; i < n; i++) {
    //         xorr ^= i ^ nums[i];
    //     }
    //     return xorr;
    // }

    int missingNumber(const vector<int>& nums) {
        int n = nums.size();
        int math_method = n;
        for (int i = 0; i < n; i++) {
            math_method += i - nums[i];
        }
        return math_method;
    }
};

// int main() {
//     Solution sol;
//     vector<int> nums1 = {0,1,2,4};
//     vector<int> nums2 = {0,1,2,3};

//     cout << sol.missingNumber(nums1) << endl;
//     cout << sol.missingNumber(nums2) << endl;

//     return 0;
// }

// int main() {
//     Solution sol;
//     string line;

//     while (true) {
//         cout << "請輸入一串數字（空格分隔，輸入 q 離開）: " << endl;
        
//         // 讀整行（支援多個數字）
//         if (!(getline(cin, line))) {
//             cout << "\n輸入錯誤, 重新輸入\n";
//             continue;
//         }
//         // 離開條件
//         if (line == "q" || line == "Q") {
//             cout << "\n退出程式\n";
//             break;
//         }

//         stringstream ss(line);
//         vector<int> nums;
//         int x;

//         // parsing
//         while(ss >> x) {
//             if (x < 0) { // 額外防呆
//                 break;
//             }
//             nums.push_back(x);
//         }
//         if (nums.empty()) {
//             cout << "❌ 輸入錯誤,請輸入非負整數(空格分隔),且不得為空\n";
//             continue;
//         }
        
//         int ans = sol.missingNumber(nums);
//         cout << "✅ 缺少的數字是: " << ans << endl;
//     }
//     return 0;
// }