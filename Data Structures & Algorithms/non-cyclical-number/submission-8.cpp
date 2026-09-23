// g++ -std=c++17 -Wall -Wextra -g3 Test.cpp -o output/Test_cpp

// # include <iostream>
// # include <vector>
// #include <sstream>
// using namespace std;
// Given: a positive integer "n"（replace it with the sum of the squares of its digits.）
// return: boolean （until the number equals 1, or it loops infinitely in a cycle）

// T / S: aim for O(logn) time and O(logn) space
// Solution: (1)Hash Set (2)Fast And Slow Pointers(Floyd's cycle detection)

class Solution {
public:
    // bool isHappy(int n) {
    //     unordered_set<int> seen;
    //     int temp = n;
    //     while (seen.find(temp) == seen.end()) {
    //         if (temp == 1) {
    //             return true;
    //         }
    //         seen.insert(temp);
    //         temp = sumOfSquares(temp);
    //     }
    //     return false;
    // }

    bool isHappy(int n) {
        int slow = n, fast = sumOfSquares(n);
        while (slow != fast) {
            if (slow == 1 || fast == 1) {
                return true;
            }
            slow = sumOfSquares(slow);
            fast = sumOfSquares(sumOfSquares(fast));
        }
        return fast == 1;
    }

public:
    int sumOfSquares(int x) {
        int res = 0;
        while (x > 0) {
            int digit = x % 10;
            digit *= digit;
            res += digit;
            x /= 10;
        }
        return res;
    }
};

// // int main() {
// //     Solution sol;
// //     vector<int> nums1 = {0,1,2,4};
// //     vector<int> nums2 = {0,1,2,3};

// //     cout << sol.missingNumber(nums1) << endl;
// //     cout << sol.missingNumber(nums2) << endl;

// //     return 0;
// // }

// int main() {
//     Solution sol;
//     string line;
//     while (true) {
//         cout << "請輸入一個數字: ";
//         if (!(getline(cin, line)) || line.empty()) {
//             cout << "輸入錯誤，請輸入一個整數！" << endl;
//             cin.clear();
//             cin.ignore(numeric_limits<streamsize>::max(), '\n');
//             continue;
//         }

//         int n;
//         try {
//             n = stoi(line);
//         }
//         catch (const std::invalid_argument& e) {
//             cout << "輸入錯誤，請輸入一個有效的整數！" << endl;
//             continue;
//         }
//         catch (const std::out_of_range& e) {
//             cout << "輸入錯誤，數字超出範圍！" << endl;
//             continue;
//         }

//         cout << "結果為:" << boolalpha << sol.isHappy(n) << endl;
//     }
// };

// // int main() {
// //     Solution sol;
// //     string line;

// //     while (true) {
// //         cout << "請輸入一串數字（空格分隔，輸入 q 離開）: " << endl;
        
// //         // 讀整行（支援多個數字）
// //         if (!(getline(cin, line))) {
// //             cout << "\n輸入錯誤, 重新輸入\n";
// //             continue;
// //         }
// //         // 離開條件
// //         if (line == "q" || line == "Q") {
// //             cout << "\n退出程式\n";
// //             break;
// //         }

// //         stringstream ss(line);
// //         vector<int> nums;
// //         int x;

// //         // parsing
// //         while(ss >> x) {
// //             if (x < 0) { // 額外防呆
// //                 break;
// //             }
// //             nums.push_back(x);
// //         }
// //         if (nums.empty()) {
// //             cout << "❌ 輸入錯誤,請輸入非負整數(空格分隔),且不得為空\n";
// //             continue;
// //         }
        
// //         int ans = sol.missingNumber(nums);
// //         cout << "✅ 缺少的數字是: " << ans << endl;
// //     }
// //     return 0;
// // }