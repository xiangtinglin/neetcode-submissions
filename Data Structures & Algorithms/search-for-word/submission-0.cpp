// clang++ .\Test.cpp -std=c++17 -o Test.exe
// .\Test.exe

// #include <iostream>
// #include <vector>
// #include <string>
// #include <set>
// #include <utility> // for std::pair
// #include <algorithm> // for std::find

// using namespace std;


/*
 [題目理解]
    # 核心: 
        1.2D Grid DFS + Backtracking
        2.不是「在整張圖找出字母」，而是：
            從某一格出發，依序匹配 word，每一步只能走上下左右，而且同一條路徑不能重複使用同一格。
        3.path:
            相鄰格子形成路徑
                    ↓
            需要搜尋可能路徑
                    ↓
            不是最短路徑，只要找到任一條
                    ↓
            DFS
                    ↓
            同一路徑不能重複使用格子
                    ↓
            visited
                    ↓
            換另一條路徑前要取消 visited
                    ↓
            DFS + Backtracking
        4.Sol:
            三個版本並不是三種不同解法： Hash Set、Visited Array、原地標記
            它們都是： DFS + Backtracking
            NeetCode 的三種方法：
            1. Backtracking（Hash Set）
            2. Backtracking（Visited Array）
            3. Backtracking（原地修改，Optimal）
            ->> 差別是：「目前路徑使c用過哪些格子」存在哪裡？
            4. Search Pruning 則是在問： 能不能提早判斷某些搜尋不可能成功，直接跳過？
*/


/*
 一、[Backtracking(Visited Array)]
    # Complexity:
        T:  O(m * 4^n)
            O(m) for double for loop.
            O(4^n) for dfs backtracking recursion.
        S:  O(m + n)
            O(m) for visited matrix
            O(n) for dfs call stack
        (Where m is the number of cells in the board and n is the length of the word.)

    # thoughts:
        1.visited: 用 vector<vector<bool>> visited; 紀錄 grid 每一個 cell 對應是否用過
        2.idea: recursion & backtracking
        3.function roles:
            dfs()：從指定起點繼續尋找「後續路徑」
            ->> regular function 負責 double for loop：尋找「起點」
*/

// class Solution {
// public:
//     // # Container: visited vector
//     vector<vector<bool>> visited;
//     int ROWS, COLS;
//     // # regular function
//     bool exist(vector<vector<char>>& board, const string& word) {
//         // 1.initial: visited vector, r, c
//         ROWS = (int)board.size(), COLS = (int)board[0].size();
//         visited.assign(ROWS, vector<bool>(COLS, false)); 
//         // 2.double for loop: call func helper
//         for (int r = 0; r < ROWS; r++) {
//             for (int c = 0; c < COLS; c++) {
//                 if (dfs(board, word, 0, r, c)) {return true;}
//             }
//         }
//         // 3.return: false
//         return false;
//     }

// private:
//     // # helper function: recursion & backtracking
//     bool dfs(vector<vector<char>>& board, const string& word, int wordIndex, int r, int c) { // 要知道t/f ->> 回傳 bool
//         // 1.if match(all the word)
//         if (wordIndex == (int)word.size()) { // word.length()也可以; 不能寫 (int)word.size() - 1 ->> 因最後一個char還沒處理
//             return true;
//         }
//         // 2.if fail: out of bound, doesn't match, visited!!!
//         if (r < 0 || r > ROWS - 1 || c < 0 || c > COLS - 1 || 
//             board[r][c] != word[wordIndex] || visited[r][c] == true) {
//                 return false;
//         }
//         // 3.recursion & backtracking: for 4 direction! (remember to update the visited!!!)
//         visited[r][c] = true;
//         bool result = dfs(board, word, wordIndex + 1, r - 1, c) ||
//                         dfs(board, word, wordIndex + 1, r + 1, c) ||
//                         dfs(board, word, wordIndex + 1, r, c - 1) ||
//                         dfs(board, word, wordIndex + 1, r, c + 1);
//         visited[r][c] = false; // 無論result 是T/F, 在return回上一層 ->> 先撤回
//         // 4.return: bool
//         return result;
//     }
// };



/*
 二、[Backtracking (Optimal)]
    T:  O(m * 4^n) for total.
        O(4^n) for dfs(4 direction, n is the height of recursion.)
        O(m) for double for loop to find the start
    S:  O(n) for total(dfs: call stack)
    (Where m is the number of cells in the board and n is the length of the word.)

    # thoughts:
        visited 只是用來記錄某格「暫時不能使用」。既然 board 本身也是可修改的，能直接借用 board 儲存 visited 狀態？
        ->> 原地標記（in-place marking）。
        ->> 暫時把已使用的格子改成一個不可能出現在 word 裡的特殊符號：'#'
        ->> '#' : true(走過), '原本char' : false(沒走過).

    # 優化了什麼？
        演算法並沒有改變： DFS + Backtracking, 改變的是 visited 狀態存放的位置.
*/

// class Solution {
// public:
//     int ROWS, COLS;
//     bool exist(vector<vector<char>>& board, string& word) {
//         // 1.initial
//         ROWS = (int)board.size(), COLS = (int)board[0].size();
//         // 2.regular function 負責 double for loop：尋找「起點」 ->> 每個cell是否符合, 交給helper判斷
//         for (int r = 0; r < ROWS; r++) {
//             for (int c = 0; c < COLS; c++) {
//                 if (dfs(board, word, 0, r, c)) {return true;}
//             }
//         }
//         // 3.return: false(all grid cell都檢查完, 都沒找到才可return 最終的 false)
//         return false;
//     }
//     // helper
//     bool dfs(vector<vector<char>>& board, string& word, int wordIndex, int r, int c) {
//         // 1.if 判斷 all words match
//         if (wordIndex == (int)word.size()) { // 不能.size() -1 ->> 當前char還需要檢查才能確定
//             return true;
//         }
//         // 2.if 判斷 fail: out of bound, 不match, 已經走過('#')
//         if (r < 0 || r >= ROWS || c < 0 || c >= COLS || board[r][c] != word[wordIndex]) {
//             return false;
//         }
//         // 3.recursion(4 directions, 記得先暫存char & 標記/撤回'#')
//         char origin = board[r][c];
//         board[r][c] = '#'; // 代表當層所在 cell (標為走過後, 開展4個方向的cell可能性)
//         bool result = dfs(board, word, wordIndex + 1, r - 1, c) ||
//                     dfs(board, word, wordIndex + 1, r + 1, c) ||
//                     dfs(board, word, wordIndex + 1, r, c - 1) ||
//                     dfs(board, word, wordIndex + 1, r, c + 1);
//         board[r][c] = origin; // 撤回: 上面進入4向下層探索回傳後回去前層要復原
//         // 4.return result;
//         return result;
//     }
// };




/*
 三、
    # thoughts: 
        1.只是改紀錄容器: vector<vector<int>> visited array; ->> hash set
*/


class Solution {
public:
    // # Container: visited vector
    set<pair<int, int>> visitedSet;
    int ROWS, COLS;
    // # regular function
    bool exist(vector<vector<char>>& board, const string& word) {
        visitedSet.clear();
        // 1.initial: visited vector, r, c
        ROWS = (int)board.size(), COLS = (int)board[0].size();
        // 2.double for loop: call func helper
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (dfs(board, word, 0, r, c)) {return true;}
            }
        }
        // 3.return: false
        return false;
    }

private:
    // # helper function: recursion & backtracking
    bool dfs(vector<vector<char>>& board, const string& word, int wordIndex, int r, int c) { // 要知道t/f ->> 回傳 bool
        // 1.if match(all the word)
        if (wordIndex == (int)word.size()) { // word.length()也可以; 不能寫 (int)word.size() - 1 ->> 因最後一個char還沒處理
            return true;
        }
        // 2.if fail: out of bound, doesn't match, visited!!!
        if (r < 0 || r > ROWS - 1 || c < 0 || c > COLS - 1 || 
            board[r][c] != word[wordIndex] || visitedSet.count({r, c})) {
                return false;
        }
        // 3.recursion & backtracking: for 4 direction! (remember to update the visited!!!)
        visitedSet.insert({r, c});
        bool result = dfs(board, word, wordIndex + 1, r - 1, c) ||
                        dfs(board, word, wordIndex + 1, r + 1, c) ||
                        dfs(board, word, wordIndex + 1, r, c - 1) ||
                        dfs(board, word, wordIndex + 1, r, c + 1);
        visitedSet.erase({r, c}); // 無論result 是T/F, 在return回上一層 ->> 先撤回
        // 4.return: bool
        return result;
    }
};


// int main() {
//     Solution sol;
//     vector<vector<char>> board = {
//         {'A','B','C','E'},
//         {'S','F','C','S'},
//         {'A','D','E','E'}
//     };

//     cout << "Board:" << endl;
//     for (const auto& row : board) {
//         for (const auto& cell : row) {
//             cout << cell << " ";
//         }
//         cout << endl;
//     }

    
//     string word;
//     cout << "Enter the word to search: ";
//     getline(cin, word); // 保留輸入所有內容, 包含空隔
//     word.erase(remove(word.begin(), word.end(), ' '), word.end()); // 移除空格, 注意在不同容器call .erase()的用法
    
//     bool result = sol.exist(board, word);
//     cout << (result ? "true" : "false") << endl; // Output: true
//     return 0;
// }