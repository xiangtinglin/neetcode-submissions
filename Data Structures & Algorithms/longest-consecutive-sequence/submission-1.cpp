// # include <iostream>
// # include <vector>
// # include <unordered_set>
// # include <algorithm>

// using namespace std;

class Solution {
public:
    // // 1️⃣ Hash Set -> T/S: O(n)
    // int longestConsecutive(vector<int>& nums) {
    //     // initialize
    //     int res = 0;
    //     unordered_set<int> store(nums.begin(), nums.end());
    //     // for loop
    //     for (int num : store) {
    //         // 回傳的不是 true / false，而是： iterator（迭代器）
    //         // store.end() 代表：走到 set 的尾巴後，也就是「沒找到」
    //         if (store.find(num - 1) == store.end()) {
    //             int curr = num;
    //             int streak = 0;
    //             while (store.find(curr) != store.end()) {
    //                 streak ++;
    //                 curr ++;
    //             }
    //             res = max(res, streak);
    //         }
    //     }
    //     return res;
    // }

    // 2️⃣ Sorting -> T: O(nlogn) S: O(1) or O(n) depending on the sorting algorithm.
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        // 先排再指定的nums[0]才正確
        sort(nums.begin(), nums.end());
        int res = 0, i = 0, streak = 0, curr = nums[0];

        while (i < nums.size()) {
            if (nums[i] != curr) {
                streak = 0;
                curr = nums[i];
            }
            while ((i < nums.size()) && (nums[i] == curr)) {
                i ++; // skip the duplicates
            }
            streak ++;
            curr ++;
            res = max(streak, res);
        }
        return res;
    }
};

// int main() {
//     vector<int> nums_1 = {100, 4, 200, 1, 3, 2};
//     vector<int> nums_2 = {0, 1, 3, 2};

//     Solution sol;
//     int res_1 = sol.longestConsecutive(nums_1);
//     int res_2 = sol.longestConsecutive(nums_2);

//     cout << "res_1: " << res_1 << endl;
//     cout << "res_2: " << res_2 << endl;

//     return 0;
// }