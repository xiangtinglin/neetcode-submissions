// // g++ -std=c++17 -Wall -Wextra -g3 Leetcode.cpp -o output/Leetcode

// # include <iostream>
// #include <limits>
// #include <vector>

// using namespace std;

class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            dp[i] = dp[i >> 1] + (i & 1);
        }
        return dp;
    }
};

// int main() {
//     Solution sol;
//     long long input;
//     while (true) {
//         cout << "請輸入一個數字: ";
//         if (!(cin >> input)) {
//             cout << "輸入錯誤，請輸入整數！" << endl;
//             cin.clear();
//             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//             continue;
//         }

//         if (input < 0 || input > INT_MAX) {
//             cout << "數值超出範圍！" << endl;
//             continue;
//         }

//         int n = static_cast<int>(input);
//         vector<int> result = sol.countBits(n);

//         cout << "1的個數: [";
//         for (size_t i = 0; i < result.size(); i++) {
//             cout << result[i];
//             if (i != result.size() - 1) {
//                 cout << ",";
//             }
//         }
//         cout << "]" << endl;
//     }
//     return 0;
// };