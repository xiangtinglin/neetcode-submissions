// // g++ -std=c++17 -Wall -Wextra -g3 Leetcode.cpp -o output/Leetcode

// # include <iostream>
// # include <cstdint>
// #include <limits>

// using namespace std;

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int res = 0;
        while (n) {
            n &= (n -1);
            res ++;
        }
        return res;
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
//         uint32_t n = static_cast<uint32_t>(input);
//         cout << "1的個數: " << sol.hammingWeight(n) << endl;
//     }
//     return 0;
// };