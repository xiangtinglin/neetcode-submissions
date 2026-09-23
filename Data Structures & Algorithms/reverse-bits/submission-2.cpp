// // g++ -std=c++17 -Wall -Wextra -g3 Leetcode.cpp -o output/Leetcode

// // # Given: 32-bit unsigned integer n
// // # Goal: reverse the bits of the binary representation of n
// // # T / S: aim for O(1) time and O(1) space.

// # include <iostream>
// #include <cstdint>   // for uint32_t
// #include <vector>
// using namespace std;

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        uint32_t res = n;
        res = ((res & 0xFFFF0000) >> 16) | ((res & 0x0000FFFF) << 16);
        res = ((res & 0xFF00FF00) >> 8) | ((res & 0x00FF00FF) << 8);
        res = ((res & 0xF0F0F0F0) >> 4) | ((res & 0x0F0F0F0F) << 4);
        res = ((res & 0xCCCCCCCC) >> 2) | ((res & 0x33333333) << 2);
        res = ((res & 0xAAAAAAAA) >> 1) | ((res & 0x55555555) << 1);
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

//         if (input < 0 || input > UINT32_MAX) {
//             cout << "數值超出範圍！" << endl;
//             continue;
//         }

//         uint32_t n = static_cast<uint32_t>(input);
//         uint32_t result = sol.reverseBits(n);
//         cout << "反轉前: " << n << endl;
//         cout << "反轉後: " << result << endl;
//     }
//     return 0;
// };