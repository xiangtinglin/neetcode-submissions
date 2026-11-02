/*
Ctrl + Shift + B：只編譯
clang++ .\Test.cpp -std=c++17 -g -Wall -Wextra -o .\Test.exe
.\Test.exe

*/

// #include <iostream>
// #include <vector>

// using namespace std;

/*
    [題目理解]
    # Given: array of integers "nums". [1, n]
    # Act: Find only one repeated number in nums
    # Return: this repeated number.
    # Must solve: 
        1.without modifying the array nums
        2.using only constant O(1) extra space.
    # note: All the integers in nums appear only once except for precisely one integer which appears two or more times.

    [解法]
    # 實際面試或刷題時，這題最重要的是：
        1. 能先寫出 Hash Set。
        2. 看出限制不允許 Hash Set／Negative Marking。
        3. 看出 value → index 的結構。
        4. 推導到 Floyd (符合題目要求, 最佳解)!!!
        (Bit Manipulation 屬於值得認識的額外解法，但不需要把它當成這題的首選。Floyd 才是最應該熟練重寫的標準答案。)
*/

/*
 一、Brute Force- T:O(n^2); S:O(1)
    # thoughts: for loop逐一計數 -> cnt = 2 者為答案!
    # Note: 不符合題目需求- linear time!
*/

// class Solution {
// public:
//     int findDuplicate(vector<int>& nums) {
//         // initial
//         int n = nums.size();
//         // for loop逐一計數 -> cnt = 2 者為答案!
//         for (int value = 1; value <= n - 1; value++) { // i = [1, n]
//             int cnt = 0; // !!!記得reset
//             for (int j = 0; j < n; j++) {
//                 if (nums[j] == value) {cnt++;}
//                 if (cnt == 2) {return value;}
//             }
//         }
//         return 0;
//     }
// };



/*
 二、Brute Force → Hash Set
    T:O(n); S:O(n) for extra space
    # thoughts: 「用"空間"省下重複搜尋"時間"」
        Brute Force太慢: 反覆掃描同一個陣列 -> 能只掃描一次，記住看過的數字？ -> Hash Set
*/

// class Solution {
// public:
//     int findDuplicate(vector<int>& nums) {
//         // 1.Create- set
//         unordered_set<int> hashSet;
//         // 2.for loop through each number in the array
//         for (int i = 0; i < nums.size(); i++) {
//             // (1)If the number is already in seen, return it
//             if (hashSet.find(nums[i]) != hashSet.end()) {return nums[i];}
//             // (2)Otherwise, insert the number into hash set.
//             hashSet.insert(nums[i]);
//         }
//         // 3.If no duplicate is found (should not happen in this problem)
//         return 0;
//     }
// };



/*
 三、Hash Set -> Negative Marking(In-place)
    T:O(n); S:O(1)
    # thoughts:
        1.時間達到O(n), 空間可優化: 擺脫額外的 hash set!
            -> 利用「數值可以轉成索引對應另一個數值 & 再改變正負號來標記」.
        2.非正解: 修改 nums，違反題目要求!
*/

// class Solution {
// public:
//     int findDuplicate(vector<int>& nums) {
//         // 1.For loop through each num of nums
//         for (int num : nums) {
//             // (1)Compute- corresponding index: [abs(num) - 1]
//             int index = abs(num) - 1;
//             // (2)If nums[abs(num) - 1] is negative: A duplicate has been found -> return
//             if (nums[index] < 0) {return abs(num);} // !記得abs()
//             // (3)Otherwise, Mark the index by the sigh *= -1
//             nums[index] *= -1;
//         }
//         // 2.If no duplicate is found (though guaranteed), return
//         return 0;
//     }
// };



/*
 四、Negative Marking(In-place) -> Fast And Slow Pointers(Floyd's)
    T:O(n); S:O(1)
    # thoughts:
        題目要求: without modifying the array nums -> 如何不修改array???
        -> 思維從「標記」變成「移動」。
    # note:
        1.有環 -> 不代表一定有重複!!!(但此題設定下, 一定有重複)
        2.一直走一定會進入環。
        3.環入口: 有2個不同位置index, 指向同一個數值(一個是從nums[0]走進環, 一個是回環)
        4.從第一次相遇點繼續前進，走到環入口的步數；期間可能多繞幾個完整環。
        5.第一次相遇「有可能」剛好就在環入口；但也可能不是 -> 不論第一次相遇在哪裡，一律執行第二階段。
*/

// class Solution {
// public:
//     int findDuplicate(vector<int>& nums) {
//         // 1.initial- slow, fast
//         int slow = 0, fast = 0;
//         // 2.Move: while (slow != fast) -> until meet first
//         while (true) {
//             slow = nums[slow];
//             fast = nums[nums[fast]];
//             if (slow == fast) {break;}
//         }
//         // 3.Start a new pointer slow2 = 0 (from start)
//         int slow2 = 0;
//         // 4.Move both: slow, slow2 -> until they meest(exactly at entry)
//         while (true) {
//             slow = nums[slow];
//             slow2 = nums[slow2];
//             if (slow == slow2) {break;}
//         }
//         return slow2; // slow也可
//     }
// };



/*
 五、另一條思路: Binary Search (on Value Range)
    T:O(n log n); S:O(1)
    # thoughts:
        1.Binary Search二分法: 不是對陣列索引搜尋nums[mid], 而是對「答案的值域」搜尋：[1, n] !
            ->  ① 答案存在於一個有順序的範圍
                ② 可以提出一個 Yes / No 問題
                ③ 這個問題能排除一半答案
        2.如何判斷重複值在哪一半？ ->> 使用鴿籠原理。
            ->> 用[1, n] 的mid + 計數 -> 判斷array中重複數值在 < or > mid
        
    # note: 
        1.不修改 nums, 額外空間 O(1)
        2.不符合: 時間複雜度
*/

// class Solution {
// public:
//     int findDuplicate(vector<int>& nums) {
//         // 1.initial (value range): [1, n], low, high
//         int high = nums.size() - 1;
//         int low = 1;
//         // 2.while (l < h)
//         while (low < high) {
//             // (1)compute: mid
//             int mid = low + ((high - low) / 2);
//             // (2)count: numbers that <= mid (in the array)
//             int cnt = 0;
//             for (int i = 0; i < nums.size(); i++) {
//                 if (nums[i] <= mid) {cnt++;}
//             }
//             // (3)if (cnt > mid), set: [low, mid] (the duplicate lies in)
//             if (cnt > mid) {high = mid;}
//             // (4)otherwise, it lies in [mid + 1, high]
//             else {low = mid + 1;} // 記得 + 1
//         }
//         // 3.return: when loop ends, the duplicate is low/high
//         return high;
//     }
// };




/*
 六、Bit Manipulation: 逐個 bit 重建重複數字
    T:O(17 bit * 2n) = O(17*n)
    S:O(1)

    # thoughts: 還有什麼額外寫法? -> 能推出重複值為何?
        1.利用題目設定: [1, n], size = n + 1
            -> 設重複值x的數量 = k, 另用基準標準比較 [1, n]、size = n
            -> (1)比起基準, nums多出x重複值的數 = (k - 1) & (2)nums少了基準某些值的數 = (k - 2)
            -> (k -1) - (k - 2) = 1 ->> nums總是比基準多1個數
        2.利用: (1) & (2)是兩者之間的落差, 其他值相同可抵消
            -> 多出(+)、缺少(-)、最終相差(+1) ->> 可否以此特性判斷每個bit是 0/1?
        3.先假設(該bit為 0/1 的情況), 找出判斷依據 -> 按bit逐一分別計算是否為"0/1"總數: 
            (此計算"1"總數)
            (1)重複值為 1: [多出] +(k - 1); [缺少] 未知-?但最多是-(k -2); 最少是-0
                ->> nums - 基準, 相減後至少 >= 1
                ->> 代表當正 >0, 重複bit都是"1"
            (2)重複值為 0: [多出] +(0); [缺少] 未知-?但最多是-(k -2); 最少是-0
                ->> nums - 基準, 相減後至少 <= 0
                ->> 代表0或負, 重複bit都是"0"
        
*/

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // 1.initial- mask, bit, x, y, n
        int ans = 0; // 若不需改, 維持原本 0
        // 2.For each bit position b from 0 to 17:
        for (int b = 0; b < 17; b++) { // 逐bit往左推算, 題目限制 1 <= n <= 10^5 ->> 只要 17bit
            // (0)Compute: mask = 1 << b. 左移
            int mask = 1 << b;
            int x = 0, y = 0; // 放這, 每輪bit -> reset
            // (1)Count nums: how many numbers in nums have this bit set, call it x.
            for (int num : nums) {
                if (num & mask) {x++;} // logistic AND: && ; bitwise AND: &
            }
            // (2)Count standard [1,n]: how many numbers from 1 to n - 1 should have this bit set, call it y.
            for (int num = 1; num < (int)nums.size(); num++) { // nums < size = n + 1 ->> [1, n]
                if (num & mask) {y++;}
            }
            // (3)Compare: If x > y, it means the duplicate has this bit set, so add it to the answer ->> | Bitwise OR
            if (x > y) {ans |= mask;} // 把 mask 植入ans
        }
        // 3.return ans
        return ans;
    }
};


// int main() {
//     Solution sol;

//     int x1, x2, x3, x4, x5;
//     cout << "Enter five integers (1 to n) with at least one duplicate.\n Remember [1, n] & length = n + 1:" << endl;
//     for (int i = 0; i < 5; i++) {
//         cout << "Enter integer " << (i + 1) << ": ";
//         cin >> x1; // Read input for each integer
//         if (i == 0) x1 = x1;
//         else if (i == 1) x2 = x1;
//         else if (i == 2) x3 = x1;
//         else if (i == 3) x4 = x1;
//         else if (i == 4) x5 = x1;
//     }

//     vector<int> nums = {x1, x2, x3, x4, x5}; // Example input, replace with actual values
//     int duplicate = sol.findDuplicate(nums);
//     cout << "The duplicate number is: " << duplicate << endl;

//     return -1;
// }