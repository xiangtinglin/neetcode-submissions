// # include <iostream>
// # include <vector>
// # include <unordered_map>
// # include <algorithm>

// using namespace std;

// Given: Given a 1-indexed array of integers numbers(already sorted in non-decreasing order)
// Goal: Your solution must use only constant extra space.
// note: Given a 1-indexed array(index從1開始)

/* Solution:
1️⃣Brutal- T:O(n^2); S:O(1)
2️⃣Binary Search- T:O(nlogn) ; S:O(1)- 因為排序好，搭配Binary search，才能不用線性搜尋
3️⃣Hash map- T:O(n); S:O(n)
4️⃣Two pointers- T:O(n), S:O(1)
*/

class Solution {
public:
    // // 1️⃣Brutal
    // vector<int> twoSum(vector<int>& numbers, int target) {
    //     for (int i = 0; i < numbers.size(); i ++) {
    //         for (int j = i + 1; j < numbers.size(); j ++) {
    //             if (numbers[i] + numbers[j] == target) {
    //                 return {i + 1, j + 1};
    //             }
    //         }
    //     }
    //     return {};
    // }

    // // 2️⃣Binary Search- T:O(nlogn) ; S:O(1)
    // vector<int> twoSum(vector<int>& numbers, int target) {
    //     for (int i = 0; i < numbers.size(); i++) {
    //         int l = i + 1, r = numbers.size() - 1;
    //         int tmp = target - numbers[i];
    //         while (l <= r) {
    //             int mid = l + (r - l) / 2;
    //             if (numbers[mid] == tmp) {
    //                 return { i + 1, mid + 1};
    //             } else if (numbers[mid] < tmp) { //檢查右邊
    //                 l = mid + 1;
    //             } else {
    //                 r = mid - 1;
    //                 }
    //         }
    //     }
    //     return {};
    // }

    // // 3️⃣Hash map- T:O(n); S:O(n)
    // vector<int> twoSum(vector<int>& numbers, int target) {
    //     unordered_map<int, int> mp;
    //     for (int i = 0; i < numbers.size(); i++) {
    //         int tmp = target - numbers[i];
    //         if (mp.count(tmp)) {
    //             return {mp[tmp], i + 1}; // 注意順序
    //         }
    //         mp[numbers[i]] = i + 1;
    //     }
    //     return {};
    // }

    // 4️⃣Two pointers- T:O(n), S:O(1)
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0, r = numbers.size() - 1;
        while (l < r) {
            int currSum = numbers[l] + numbers[r];
            if (currSum < target) {
                l++;
            } else if (currSum > target) {
                r--;
            } else {
                return { l + 1, r + 1 };
            }
        }
        return {};
    }
};

// int main() {

//     vector<int> nums_1 = {2, 7, 11, 15}; // 注意: exactly one solution
//     vector<int> nums_2 = {1, 3, 6, 10};

//     Solution sol;
//     vector<int> res_1 = sol.twoSum(nums_1, 9);
//     vector<int> res_2 = sol.twoSum(nums_2, 16);

//     cout << "res_1: ";
//     for (int x : res_1) { cout << x << " ";}
//     cout << endl;

//     cout << "res_2: ";
//     for (int x : res_2) { cout << x << " ";}
//     cout << endl;

//     return 0;
// }