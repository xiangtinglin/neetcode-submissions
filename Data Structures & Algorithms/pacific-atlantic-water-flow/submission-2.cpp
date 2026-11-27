
// clang++ .\Test.cpp -std=c++17 -o Test.exe
// .\Test.exe

// #include <iostream>
// #include <queue>
// #include <vector>

// using namespace std;

/*
 [題目理解]
    # Given:
        1.m x n rectangular island
            the int inside the cell: heights[r][c]
    # return:
        1.2D list of grid coordinates result where result[i] = [ri, ci]: 
            rain water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.
    # note:     
        1.there are other possible paths for these cells to flow to the Pacific and Atlantic oceans.
    # thoughts:
        1.這題的核心不是「水怎麼往海流」，而是：
            從兩個海洋的邊界反向出發，找出哪些高地能夠回到這個海洋。這個「反向思考」是整題最關鍵、也最容易卡住的地方。
        2.水只能往上下左右移動，而且只能：從較高或相同高度 → 較低或相同高度
            ex. heights[nr][nc] <= heights[r][c]
        3.我們要找的是：
            能流到 Pacific 的格子 ∩ 能流到 Atlantic 的格子 ->> 同時能到兩個海洋的格子。
    # Sol:
        1.最直覺的暴力法: 對每一個格子做 DFS，模擬水從這裡往低處流，看最後是否能碰到兩個海洋。
            ->> 容易超時。
            ->> 所以問題變成：能不能不要從每個格子分別搜尋？
        2.(反向思考: 如果從海洋出發，反向往島內走，可以走到哪些格子？)
            (1)需要搜尋兩次, 我們分別建立兩張 visited 表： atl[r][c], Pac[r][c]
                ->> 表示 (r,c) 的水能流到 Atlantic。
            (2)接著：
                - 從 Pacific 的所有邊界做 DFS。
                - 從 Atlantic 的所有邊界做 DFS。
                - 找出兩張表都是 true 的格子。
*/


/*
 一、[Brute Force (Backtracking) (Time Limit Exceeded)]
    T:  O(m * n * 4^(m * n)) for total.
        O(m * n) for nested for loop
        O(4^(m * n)) for the worst dfs.
    S:  O(m * n) for the worst extra space(dfs call stack).
    (Where m is the number of rows and n is the number of columns.)

    # thoughts:
        1.「正向搜尋」。它從每個陸地格子出發，沿著水真正會流動的方向搜尋：
            搜尋起點是：所有陸地格子
            而搜尋目標是：Pacific / Atlantic
            方向為：陸地格子 → 海洋
            ->> 目前格子（高） → 鄰居格子（低或相同） → 海洋
        2. container: 
            (1)res
            (2)不用vector<vector<int>> visited; ->> 直接改/撤回 走過的height數值 ->> 避免: heights相等, 造成的無限loop回流 ->> 設定走過的height為最高(就不會回流)
        3. target: 知道每一個cell最終會不會走進2個ocean(bool pac, atl)
*/

// class Solution {
// public:
//     // shared container & initial
//     int ROWS, COLS;
//     bool pac, atl; // label final entry
//     vector<vector<int>> directions = {
//         {-1, 0},
//         {1, 0},
//         {0, -1},
//         {0, 1}
//     };
//     // regular func
//     vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
//         // 1.initial
//         vector<vector<int>> res;
//         ROWS = (int)heights.size(), COLS = (int)heights[0].size();
//         pac = false, atl = false;
//         // 2.traverse each heights to find and push to res
//         for (int r = 0; r < ROWS; r++) {
//             for (int c = 0; c < COLS; c++) {
//                 // (1)initial
//                 pac = false, atl = false;
//                 // (2)call helper func- dfs
//                 dfs(heights, r, c, INT_MAX); // the processing of labeling pac, atl
//                 // (3)find the target & push to res
//                 if (pac && atl) {
//                     res.push_back({r, c});
//                 }
//             }
//         }
//         // 3.return res;
//         return res;
//     }

// private:
//     // helper func- dfs(to label T/F: pacific, atlantic)
//     void dfs(vector<vector<int>>& heights, int r, int c, int prevH) {
//         // 1.if (out of bound 左/上) {pac}
//         if (r < 0 || c < 0) {
//             pac = true;
//             return; // 到底, 要回上層
//         }
//         // 2.if (out of bound 右/下) {atl}
//         if (r >= ROWS || c >= COLS) {
//             atl = true;
//             return;
//         }
//         // 3.if (curH > prevH) {return false;}
//         if (heights[r][c] > prevH) {
//             return; // 流不出去
//         }
//         // 4.temporarily store the visited & explore the 4 directions cells recursively(dfs)
//         int tmp = heights[r][c];
//         heights[r][c] = INT_MAX; // 確保進入下一層時, 當等高時 不會回流prevH ->> 造成dead loop
//         for (auto& dir : directions) { // 記得 & , 否則: 每次都copy ->> 超時
//             dfs(heights, r + dir[0], c + dir[1], tmp);
//             if (pac && atl) {break;} // 若都收集到, 可直接跳出fpr loop
//         }
//         // 5.restore the visited(for next starting cell)
//         heights[r][c] = tmp; // 記得復原, 為了下一個起點重置
//     }
// };



/*
 二、[Depth First Search- Optimal(reverse)]
    T:  O(m * n) for total.
        O(m * n) for traversing pac/atl intersection(both true then push_back)
        O(2 * m * n) for dfs(pac & atl recursion call stack): 不是O(4^(m*n)), 因為 !ocean[nr][nc] 保證每個格子對每個海洋最多只會被完整處理一次。
    S:  O(m * n)
        O(m * n) for the worst-case recursion call stack(dfs)
        O(2 * m * n) for extra space: vector<vecotr<bool>> pac, atl;
    (Where m is the number of rows and n is the number of columns.)

    # thoughts:
        1.暴力法慢在哪裡？
            for (每個格子) {
                從這格 DFS，看能否到 Pacific 和 Atlantic;
            }
            ex. 多個起點最後共用同一段路 ->> X → Y → Pacific 會重複搜尋三次：
                A ─┐
                B ─┼→ X → Y → Pacific
                C ─┘
            ->> 反過來問：從 Pacific 邊界反向出發，可以走到哪些陸地格子？
        2.口訣：
            正向：水往低處流
            反向：從海洋往高處爬: nextHeight >= currentHeight
            ->> 要準備兩張 visited 表: vector<vector<bool>> pac/atl
                ex. pac[r][c] == true
                    從 Pacific 反向可以走到 (r,c)。 ->> 等價於： (r,c) 的水正向可以流到 Pacific。
            ->> 最後答案就是交集
        3.這不是每個起點各自建立 visited，而是：
            所有 Pacific 邊界共用 pac
            所有 Atlantic 邊界共用 atl
            ->> 所以走過的區域不會重複展開。
            ->> 反向解法不再針對單一起點回答 true/false，而是標記整片可達區域：
        4.!ocean[nr][nc], 不是表示： 確定能入海的格子不能用。
            而是表示： 這個格子已經處理完畢，不需要再次展開。
            ->> 如果沒有, 相同高度的相鄰格子會互相遞迴，形成無限循環，最後 stack overflow

            ocean[nr][nc] == true 有兩層意思：
                1. 已經確定 (nr,nc) 能到這個海洋。
                2. 第一次進入它時，已經從它繼續探索過所有合法鄰居。 ->> 因此再次遇到它時，不需要重做相同工作。
*/

// class Solution {
// public:
//     // 1.shared containers, initial: directions, ROWS/COLS
//     int ROWS, COLS;
//     vector<pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
//     // regular func
//     vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
//         // 1.initial: r/c, vector<vector<bool>> pac/atl, res
//         ROWS = (int)heights.size(), COLS = (int)heights[0].size();
//         vector<vector<bool>> pac(ROWS, vector<bool>(COLS, false));
//         vector<vector<bool>> atl(ROWS, vector<bool>(COLS, false));
//         vector<vector<int>> res;
//         // 2.from (1)pac (2)atl: call helper dfs: if (pac && atl) {push}
//         for (int r = 0; r < ROWS; r++) {
//             dfs(heights, pac, r, 0); // 不用傳prevH ->> 用別的方法避免回流dead loop
//             dfs(heights, atl, r, COLS - 1);
//         }
//         for (int c = 0; c < COLS; c++) {
//             dfs(heights, pac, 0, c);
//             dfs(heights, atl, ROWS - 1, c);
//         }
//         for (int r = 0; r < ROWS; r++) {
//             for (int c = 0; c < COLS; c++) {
//                 if (pac[r][c] && atl[r][c]) {
//                     res.push_back({r, c});
//                 }
//             }
//         }
//         // 3.return res;
//         return res;
//     }

//     // helper- dfs
//     void dfs(vector<vector<int>>& heights, vector<vector<bool>>& ocean, int r, int c) {
//         // 1.initial: starting cell = true;
//         ocean[r][c] = true;
//         // 2.for 4 directions:
//         for (auto& [dr, dc] : directions) {
//             // (1)from ocean(pac/atl): if (in the bound && !ocean[r][c] && height[r][c] >= prvH) {pac[r][c] = t}
//             int nr = r + dr, nc = c + dc;
//             if (nr >= 0 && nc >= 0 && nr < ROWS && nc < COLS && 
//             !ocean[nr][nc] && heights[nr][nc] >= heights[r][c]) {
//                 dfs(heights, ocean, nr, nc);
//             }
//         }
//     }
// };



/*
 三、[Breadth Search First]: Do the same “reverse flow” idea, but with BFS.
    T:  O(m * n)
        O(2 * (m + n)) for push the border-cells to two ocean queues
        O(2 * (m * n)) for the worst-case of two round call bfs
        O(m * n) for traversing all grids cell to find & push the intersection of two ocean boolean grids.
    S:  O(m * n)
        O(2 * m * n) for two ocean queues.
        O(2 * m * n) for two ocean boolean grids.
    (where m is the number of rows and n is the number of cols)

    # thoughts:
*/

class Solution {
public:
    // shared container, initial: 4 directions
    int ROWS, COLS;
    vector<vector<int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}
    };
    // [regular]
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        // 1.initial: two boolean grids, two to-do cells source queue
        ROWS = (int)heights.size(), COLS = (int)heights[0].size();
        vector<vector<int>> res;
        vector<vector<bool>> pacB(ROWS, vector<bool>(COLS, false));
        vector<vector<bool>> atlB(ROWS, vector<bool>(COLS, false));

        queue<pair<int, int>> pacQ, atlQ;
        // 2.traverse the border cells of pac/atl
        for (int r = 0; r < ROWS; r++) {
            // (1)push all border-starting cells
            pacQ.push({r, 0});
            atlQ.push({r, COLS - 1});
        }
        for (int c = 0; c < COLS; c++) {
            pacQ.push({0, c});
            atlQ.push({ROWS - 1, c});
        }
        // 3.call bfs for two source queue
        bfs(heights, pacB, pacQ);
        bfs(heights, atlB, atlQ);
        // 4.iterate all cells; if (pac/atl both true), add the cell to res;
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (pacB[r][c] && atlB[r][c]) {
                    res.push_back({r, c});
                }
            }
        }
        return res;
    }
private:
    // [helper]
    void bfs(vector<vector<int>>& heights, vector<vector<bool>>& oceanB, queue<pair<int, int>>& oceanQ) { 
        // {r, c} 都push進queue ->> 不需要傳入int r, c
        // while(queue is not empty)
        while (!oceanQ.empty()) {
            auto [r, c] = oceanQ.front(); oceanQ.pop(); // push 進queue的都必是 true!; auto不能用& ->> 後面直接pop()後, reference會失效!
            // (1)traverse the 4 directions of each cell
            for (auto& d : directions) {
                // (i)if (int the bound && not visited && heights[nr][nc] >= heights[r][c]), push into queue.
                int nr = r + d[0], nc = c + d[1];
                oceanB[r][c] = true;

                if (nr >= 0 && nc >= 0 && nr < ROWS && nc < COLS && 
                !oceanB[nr][nc] && heights[nr][nc] >= heights[r][c]) {
                    oceanQ.push({nr, nc}); // push 進queue的都必是 true!; {r, c} 原本就在queue ->> 要檢查{nr, nc}界線!!!
                }
            }
        }
    }
};



// int main() {
//     Solution sol;
//     vector<vector<int>> heights;
//     for (int i = 0; i < 5; i++) {
//         vector<int> row;
//         for (int j = 0; j < 5; j++) {
//             row.push_back(rand() % 100); // Example values, you can modify as needed
//         }
//         heights.push_back(row);
//     }
//     cout << "[Heights Matrix]:" << endl;
//     for (const auto& row : heights) {
//         for (const auto& val : row) {
//             cout << val << " ";
//         }
//         cout << endl;
//     }

//     vector<vector<int>> result = sol.pacificAtlantic(heights);
//     cout << endl <<"[Cells that can flow to both oceans]:" << endl;
//     for (const auto& cell : result) {
//         cout << "[" << cell[0] << ", " << cell[1] << "]" << endl;
//     }

//     return 0;
// };