// # include <iostream>
// # include <vector>
// # include <unordered_map>
// # include <algorithm>

// using namespace std;

/* 
# note:
1. the indices i, j and k are all distinct.
2. solution set must not contain duplicate triplets.
    （Within each triplet, the three indices must be distinct. However, the same index may be used in different triplets.）
3. return the output and the triplets in any order.

# Solutions:
1️⃣ Brute Force- T:O(n^3), S:O(m + log n) 最壞O(n^2)

*/
class Solution {
public:
//     // 1️⃣ Brute Force- T:O(n^3), S:O(m + log n) 最壞O(n^2)
//     // O(m) is used for storing unique triplets in a set. 
//     // In the worst case, m is O(n^2).
//     vector<vector<int>> threeSum(vector<int>& nums) {
//         set<vector<int>> res;
//         sort(nums.begin(), nums.end());
//         // ⚠️寫 nums.size() - 2 ，有陷阱！型別size_t 可能unsigned underflow
//         for (int i = 0; i < nums.size(); i++ ) {
//             for (int j = i + 1; j < nums.size(); j++) {
//                 for (int k = j + 1; k < nums.size(); k++) {
//                     if (nums[i] + nums[j] + nums[k] == 0) {
//                         res.insert({nums[i], nums[j], nums[k]});
//                     }
//                 }

//             }
//         }
//         return vector<vector<int>>(res.begin(), res.end());
//     }

    // // 2️⃣ Hash Map- T:O(n^2), S:O(n)最壞O(n^2) in the worst case
    // // 找int target = -(nums[i] + nums[j]);
    // vector<vector<int>> threeSum(vector<int> &nums) {
    //     unordered_map<int, int> count;
    //     sort(nums.begin(), nums.end());
    //     vector<vector<int>> res;

    //     for (int num:nums) {
    //         count[num] ++;
    //     }
    //     for (int i = 0; i < nums.size(); i++) {
    //         count[nums[i]] --;
    //         //第一次會算全部組合，之後重複開頭數字才會跳過
    //         if ((i > 0) && (nums[i] == nums[i - 1])) { 
    //             continue;
    //         }
    //         for (int j = i + 1; j < nums.size(); j++) {
    //             count[nums[j]] --;
    //             if ((j > i + 1) && (nums[j] == nums[j - 1])) {
    //                 continue;
    //             }
    //             int target = -(nums[i] + nums[j]);
    //             if (count[target] > 0) {
    //                 res.push_back({nums[i], nums[j], target}); //⚠️ vector用{}
    //             }
    //         }
    //         for (int j = i + 1; j < nums.size(); j++) { //⚠️記得宣告: int j
    //             count[nums[j]]++;
    //         }
    //     }
    //     return res;
    // }
    // 3️⃣Two Pointers
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) break;
            if ((i > 0) && (nums[i] == nums[i - 1])) continue;

            int l = i + 1, r = nums.size() - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum > 0) {
                    r--;
                } else if (sum < 0) {
                    l++;
                } else {
                    res.push_back({nums[i], nums[l], nums[r]});
                    l++;
                    r--;
                    while ((l < r) && (nums[l] == nums[l - 1])) {
                        l++;
                    }
                    while ((l < r) && (nums[r] == nums[r + 1])) {
                        r--;
                    }
                }
            }
        }
        return res;
    }
};

// int main() {

//     vector<int> nums_1 = {0, 2, -2 ,7, 11, 15};
//     vector<int> nums_2 = {1, 3, 6, 10};

//     Solution sol;
//     vector<vector<int>> res_1 = sol.threeSum(nums_1);
//     vector<vector<int>> res_2 = sol.threeSum(nums_2);

//     cout << "res_1: ";
//     cout << "[";
//     for (const auto& triplet : res_1) {
//         cout << "[";
//         for (int x : triplet) { cout << x << " ";}
//         cout << "] ";
//     }
//     cout << "]";
//     cout << endl;

//     cout << "res_2: ";
    
//     cout << "[";
//     for (const auto& triplet : res_2) {
//         cout << "[";
//         for (int x : triplet) { cout << x << " ";}
//         cout << "] ";
//     }
//     cout << "]";
//     cout << endl;

//     return 0;
// }