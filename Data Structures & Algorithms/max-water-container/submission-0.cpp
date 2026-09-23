/*
width = index = r - l
height = min(height[l], height[r])
*/

// # include <iostream>
// # include <vector>
// # include <unordered_map>
// # include <algorithm>

// using namespace std;

class Solution {
public:
//     // 1️⃣ Brute Force- T:O(n^2) / S:O(1)
//     int maxArea(vector<int>& height) {
//         int res = 0;
//         for (int i = 0; i < height.size(); i++) {
//             for (int j = i + 1; j < height.size(); j++) {
//                 int w = j - i;
//                 int h = min(height[i], height[j]);
//                 int tmp = w * h;
//                 res = max(tmp, res);
//             }
//         }
//         return res;
//     }
    // 2️⃣ Two pointers- T:O(n), S:O(1)
    // 💡問題被簡化成: 寬度變小的情況下，怎麼讓高度有機會變大？
        // 現在左邊比較矮
        //     → 先計算它和目前最遠右邊的面積
        //     → 證明它和任何更靠內的右邊配對都不可能更大
        //     → 這根左 bar 的所有可能性已處理完
        //     → 安全放棄它
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int res = 0;
        while (l < r) {
            int tmp = (r - l) * min(height[l], height[r]);
            res = max(tmp, res);

            if (height[l] <= height[r]) {
                l++;
            } else {
                r--;
            }
        }
        return res;
    }
};

// int main() {

//     vector<int> nums_1 = {0, 2, -2 ,7, 11, 15};
//     vector<int> nums_2 = {1, 3, 6, 10};

//     Solution sol;
//     int res_1 = sol.maxArea(nums_1);
//     int res_2 = sol.maxArea(nums_2);

//     cout << "res_1: " << res_1 << endl;
//     cout << "res_2: " << res_2 << endl;

//     return 0;
// }