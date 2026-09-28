/*
Ctrl + Shift + B：只編譯

clang++ -std=c++17 Test.cpp -o Test.exe
.\Test.exe

*/

// # include<iostream>
// # include<vector>
// using namespace std;

/*
    Given: int array "nums"、int "target"
    Return: index of "target" or -1(not found)
    Must: O(log n) Time
*/


/*
    1. Brute Force- T:O(n); S:O(1)
*/

// class Solution {
// public:
//     int search(vector<int>& nums, int target) {
//         for (int i = 0; i < nums.size(); i++) {
//             if (nums[i] == target) {
//                 return i;
//             }
//         }
//         return -1;
//     }
// };


/*
    2. Binary Search & 3. Binary Search(2 pass)- T:O(log n); S:O(1)
        # 核心概念:
            (1)若rotated -> 無法靠跟mid比大小,確定尋找方向 
                -> 先找出rotated pivot(最小值 index)
            (2)有pivot後, 拆2邊分別搜尋
                -> 搜尋可寫成函式重複使用
            -> 把題目拆成2個已經會的問題：
                153. Find Minimum in Rotated Sorted Array
                +
                一般 Binary Search
*/

// class Solution {
// public:
//     int search(vector<int>& nums, int target) {
//         // (1)找出pivot(最小值index)
//         int n = nums.size();
//         int l = 0, r = n - 1;
//         while (l < r) {
//             int m = l + ((r - l) / 2);
//             if (nums[m] > nums[r]) {
//                 l = m + 1;
//             } else {r = m;}
//         }
//         int p = l;
//         // (2)分2邊binary search
//         if (target >= nums[p] && target <= nums[n - 1]) {
//             return binarySearch(nums, target, p, n - 1);
//         }
//         return binarySearch(nums, target, 0, p - 1);
//     }
//     // 函式- sorted array純binary search
//     int binarySearch(vector<int>& nums, int target, int l, int r) {
//         while (l <= r) {
//             int m = l + (r - l) / 2;
//             if (nums[m] < target) {
//                 l = m + 1;
//             } else if (nums[m] > target) {
//                 r = m - 1;
//             } else {return m;}
//         }
//         return -1;
//     }
// };


/*
    4. Binary Search(1 pass)- T:O(); S:O()
        # 核心概念: 
            (1)不找rotated pivot分2路 -> 用mid持續找 target + 判斷旋轉問題
            (2)每次先判斷: mid哪邊是sorted -> 分情況處理(判斷式寫法不同)
                再判斷: target在mid哪邊? 
*/

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = nums.size();
        int l = 0, r = n - 1;

        while (l <= r) {
            int m = l + ((r - l) / 2);
            if (nums[m] == target) {return m;}

            if (nums[m] <= nums[r]) {
                if (target <= nums[r] && nums[m] < target) {l = m + 1;}
                else {r = m - 1;} // 前面優先檢查 nums[m] == target -> 才可寫 l = m - 1 (否則漏掉mid本身); l 或 r要=否則會漏
            } else {
                if (nums[l] <= target && target < nums[m]) {r = m - 1;}
                else {l = m + 1;}
            }
        }
        return -1;
    }
};


// int main() {
//     Solution sol;
//     vector<int> nums = {4,5,6,7,0,1,2};
//     int target = 2;
//     cout << "Target: " << target << " found at index: " << sol.search(nums, target) << endl;
    
//     return 0;
// }