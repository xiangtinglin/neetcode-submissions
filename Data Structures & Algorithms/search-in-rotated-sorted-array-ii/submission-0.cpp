/*
Ctrl + Shift + B：只編譯

clang++ -std=c++17 Test.cpp -o Test.exe
.\Test.exe

*/


/*
    1. Given: 
        (1)int array "nums" sorted (non-decreasing)(not necessarily with distinct values).
        (2)int "target"
    2. Return: true(in "nums") or false
    3. Must:  decrease the overall operation steps as much as possible.
*/

// #include <iostream>
// #include <vector>
// using namespace std;

/*
    1. Brute Force- T:O(n); S:O(1)
*/

// class Solution {
// public:
//     bool search(vector<int>& nums, int target) {
//         for (int i = 0; i < nums.size(); i++) {
//             if (nums[i] == target) {return true;}
//         }
//         return false;
//     }
// };



/*
    2. Binary Search- 
        T: O(log n) in average case,  
           O(n) worst-case when all elements are duplicates except one.
            ex. [1,0,1,1,1]、[1,1,1,0,1]
        S:O(1)
    # 注意:  nums[l] == nums[m], 2邊都有可能, 必須特別處理 -> 否則無法判斷哪邊, 可能錯過。 ex. [1,0,1,1,1]、[1,1,1,0,1]
*/

class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int n = nums.size();
        int l = 0, r = n - 1;

        while (l <= r) {
            int m = l + ((r - l) / 2);
            if (nums[m] == target) {return true;}

            if (nums[l] < nums[m]) { // left portion(sorted)
                if (nums[l] <= target && target < nums[m]) {r = m - 1;} 
                else {l = m + 1;}
            } else if (nums[l] > nums[m]) {
                if (nums[m] < target && target <= nums[r]) {l = m + 1;}
                else {r = m - 1;}
            } else {l++;} // !!! nums[l] == nums[m], 2邊都有可能, 必須特別處理 -> 否則無法判斷哪邊, 可能錯過。 ex. [1,0,1,1,1]、[1,1,1,0,1]
        }
        return false;
    }
};


// int main() {
//     Solution sol;
//     vector<int> nums = {1, 1, 1, 1, 1, 0, 1};
//     int target = 0;
//     cout << (sol.search(nums, target)? "T!" : "F!") << endl;
//     return 0;
// }