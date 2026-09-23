// # include <iostream>
// # include <vector>

// using namespace std;

/*
# 題目:
    1. given: int matrix(m*n)、int target
    2. return: true / false
# 限制: 
    1. O(log(m * n)) time complexity.
    2. Each row: sorted in increasing order.
    3. The first integer of each row: greater than the last integer of the previous row.
    4. 🔥You must write a solution in O(log(m * n)) time complexity.
*/

/*
1️⃣ Brute Force- T:O(m * n); S:O(1)
    (Where m is the number of rows and n is the number of columns of matrix.)
*/

// class Solution {
// public:
//     bool searchMatrix(vector<vector<int>>& matrix, int target) {
//         for (int r = 0; r < matrix.size(); r++) {
//             for (int c = 0; c < matrix[r].size(); c++) {
//                 if (matrix[r][c] == target) {
//                     return true;
//                 }
//             }
//         }
//         return false;
//     }
// };

/*
2️⃣ Staircase Search- T:O(m + n); S:O(1)
    # 概念:
        1. each row / column is sorted left-to-right / top-to-bottom
            -> * an entire row or column
        2. Start from the top-right corner
            -> keep moving until find the target / move out of bounds.
*/

// class Solution {
// public:
//     bool searchMatrix(vector<vector<int>>& matrix, int target) {
//         // (1) 定義: 界線、起始點
//         int m = matrix.size(), n = matrix[0].size();
//         int r = 0, c = n - 1;
//         // (2) while範圍內
//         while (r < m && c >= 0) {
//             if (matrix[r][c] < target) {
//                 r++;
//             } else if (matrix[r][c] > target) {
//                 c--;
//             } else {
//                 return true; // ⚠️可直接return true, 不用break
//             }
//         }
//         return false; // Out of bounds! -> 無
//     }
// };

/*
3️⃣ Binary Search- 
    T:O(log m + log n), (which reduces to O(log(m * n)))
    S:O(1)
    # 概念: apply binary search twice(First the rows -> columns)
*/

// class Solution {
// public:
//     bool searchMatrix(vector<vector<int>>& matrix, int target) {
//         int ROWS = matrix.size();
//         int COLS = matrix[0].size();

//         int top = 0, bottom = ROWS - 1;
//         while (top <= bottom) {
//             int midR = (top + bottom) / 2;
//             if (target < matrix[midR][0]) {
//                 bottom = midR - 1;
//             } else if (target > matrix[midR][COLS - 1]) {
//                 top = midR + 1;
//             } else {
//                 break;
//             }
//         }
//         if (!(top <= bottom)) {return false;}

//         int l = 0, r = COLS - 1;
//         int currRow = (top + bottom) / 2;
//         while (l <= r) {
//             int midC = (l + r) / 2;
//             if (target < matrix[currRow][midC]) {
//                 r = midC - 1;
//             } else if (target > matrix[currRow][midC]) {
//                 l = midC + 1;
//             } else {return true;}
//         }
//         return false;
//     }
// };

/*
4️⃣ 🏆Binary Search (One Pass)- T:O(log m * n); S:O(1)
    # 核心概念: 🔥這個 2D matrix 其實等價於一條 sorted 1D array。
        1. run one binary search from index 0 to ROWS * COLS - 1
        2. For any mid index m: 
            row = m // COLS
            col = m % COLS
*/

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int ROWS = matrix.size();
        int COLS = matrix[0].size();

        int l = 0, r = ROWS * COLS - 1;
        while (l <= r) {
            int m = l + ((r -l) / 2); //⚠️ (l + r)可能太大 -> 避免溢位
            int row = m / COLS, col = m % COLS;
            if (target < matrix[row][col]) {
                r = m - 1;
            } else if (target > matrix[row][col]) {
                l = m + 1;
            } else {
                return true;
            }
        }
        return false;
    }
};


// int main() {
//     Solution solution;
//     vector<vector<int>> matrix = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
//     int target = 13;
//     bool result = solution.searchMatrix(matrix, target);
//     cout << (result ? "true" : "false") << endl; 
//     return 0;
// }