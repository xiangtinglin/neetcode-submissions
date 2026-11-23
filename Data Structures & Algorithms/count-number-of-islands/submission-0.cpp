// clang++ .\Test.cpp -std=c++17 -o Test.exe
// .\Test.exe

// #include <iostream>
// #include <utility>
// #include <vector>

// using namespace std;

/*
 [題目理解]
    # Q: given a grid(2D, 0/1), return the number of islands
    # thoughts:
        1.遇到"1": 繼續找4個方向中也連續為"1"的char, 放進queue中 & 標記走過的路
            ->> 重複動作, 直到queue都空(沒有任何"1", 代表周圍都是"0"(含邊界)了) 
            ->> 從單一起點, 到整round跑完, island數 +1
          ->> 繼續找下一個起點(沒走過 & 為"1")

*/


/*
 一、[DFS(without queue) & in-place mark used]
    T:  O(m * n) for total.
        O(m * n) for double for loop
        O(m * n) for all the cells in dfs = each cell for 1 time searched
    S:  O(m * n) for call stack(dfs), worst case: all are '1'
    (Where m is the number of rows and n is the number of columns in the grid.)
    
    # [重點]: 
        1.這題的 DFS 目的不是「找出所有可能路徑」，而是「把整座島全部標記成已走過」。
            ->> 所以走過的陸地必須永久保留為 visited，不能撤回!!!
            ->> (不管起始點是哪個, 連接同一個island內不能重複計算!)
        2.區別- Backtracking：探索所有可能的路徑(所以才要撤回)
*/

// class Solution {
// public:
//     // shared container, initial
//     vector<pair<int, int>> directions = { // 可以用int array[4][2], 或vector<pair<int, int>>;
//         {-1, 0},
//         {1, 0},
//         {0, -1},
//         {0, 1}
//     };
//     int ROWS, COLS;

//     int numIslands(vector<vector<char>>& grid) {
//         // 1.initial
//         ROWS = (int)grid.size(), COLS = (int)grid[0].size();
//         int island = 0;
//         // 2.double for loop: to find the proper start("1" & unused)
//         for (int r = 0; r < ROWS; r++) {
//             for (int c = 0; c < COLS; c++) {
//                 // (1)if (find "1") {island++ & dfs(4 directions)}
//                 if (grid[r][c] == '1') { // 注意: char 用 '', string才用 ""
//                     island++;
//                     dfs(grid, r, c); // 同island都要mark: used
//                 }
//             }
//         }
//         // 3.return total num
//         return island;
//     }

// private:
//     // helper- dfs: check the range & mark of the same island
//     void dfs(vector<vector<char>>& grid, int r, int c) {
//         // 1.if (fail: out of bound, is water, used path "#") {return}
//         if (r < 0 || c < 0 || r >= ROWS || c >= COLS ||
//             grid[r][c] == '0' || grid[r][c] == '#') {
//                 return;
//             }
//         // 2.if (is "1") {mark used "#"}
//         if (grid[r][c] == '1') {grid[r][c] = '#';}
//         // 3.for (4 directions pair) {dfs()}
//         for (auto& [dr, dc] : directions) {
//             dfs(grid, r + dr, c + dc);
//         }
//     }
// };


/*
 二、[BFS 搭配 queue]
    T:  O(m * n) for total.
        O(m * n) for double for loop
        O(m * n) for total BFS(each cell at most 1 time searched)
    S:  O(m * n) for queue the worst
    (Where m is the number of rows and n is the number of columns in the grid.)

    # thoughts: 除了DFS, 還能BFS搭配queue!
        BFS：一圈一圈擴散
            找到陸地
            → 先處理所有距離 1 格的陸地
            → 再處理所有距離 2 格的陸地
            → 繼續向外擴散
*/

// class Solution {
// public:
//     // shared initial & container: R, C
//     int ROWS, COLS;
//     // regular func
//     int numIslands(vector<vector<char>>& grid) {
//         // 1.initial
//         ROWS = (int)grid.size(), COLS = (int)grid[0].size();
//         int island = 0;
//         // 2.double for loop
//         for (int r = 0; r < ROWS; r++) {
//             for (int c = 0; c < COLS; c++) {
//                 // (1)if (find the start '1') {island++ & bfs()}
//                 if (grid[r][c] == '1') {
//                     bfs(grid, r, c);
//                     island++;
//                 }
//             }
//         }
//         // 3.return total num
//         return island;
//     }

// private:    
//     // initial
//     queue<pair<int, int>> q;
//     vector<pair<int, int>> directions = {
//         {-1, 0},
//         {1, 0},
//         {0, -1},
//         {0, 1}
//     };
//     // helper: bfs
//     void bfs(vector<vector<char>>& grid, int r, int c) { 
//         // 1.push [r, c] of the start '1' in q & marked used '#'
//         q.push({r, c});
//         grid[r][c] = '#';
//         // 2.while (q is not empty) {front then pop the cell; explore the 4 directions; if (neibor is '1'(not used) & in the bound) {push to q & marked used} }s
//         while (!q.empty()) {
//             auto p = q.front(); q.pop(); // 若.front後馬上pop, 不能用 reference & !!!或要更後面才pop
//             int curR = p.first, curC = p.second;

//             for (auto& [dr, dc] : directions) {
//                 int nR = curR + dr, nC = curC + dc;
//                 if (nR >= 0 && nC >= 0 && nR < ROWS && nC < COLS &&
//                     grid[nR][nC] == '1') {
//                         q.push({nR, nC});
//                         grid[nR][nC] = '#';
//                     }
//             }
//         }
//     }
// };




/*
 三、[Union-Find / DSU（Disjoint Set Union）]
    T:  O(m * n) for traverse the grid cells
        - 雙層迴圈：O(mn)
        - 每格最多檢查上、左兩個方向
        - find / unite：攤銷 O(α(mn))
    S:  O(m * n) for extra space: container(parent, size)
        - parent：O(mn)
        - size：O(mn)

    # thoughts:
        1.它的思考方式和 DFS/BFS 完全不同：
            DFS/BFS：從一格陸地出發，把整座島走完
            Union-Find：先把每格陸地看成獨立島嶼，再把相鄰島嶼合併
    # Act:
        1.DSU:
            節點：   0 1 2 3 4 (unique index- 1D)
            parent： 0 1 2 3 4 (每個節點一開始都是自己的 root：也就是每個格子暫時屬於不同集合。)
            size：   1 1 1 1 1 (island size)
        2.`find()`：找到集合的 
            trick: Path Compression
                原本： 3 → 2 → 1 → 0
                執行 find(3) 後，壓縮成：
                    3 ─┐
                    2 ─┼→ 0
                    1 ─┘
                下一次查詢就可以更快找到 root。
        3.`unite()`：合併兩個集合
*/

// 新增data structure(新class): Treat each cell as a node and map (row, col) to a unique index.
// 需要table (1)辨識是否為同個island union: find root (2)bool unite: 同則不用合併, 不同root則要合併
class DSU {
    // initial, container
    vector<int> parent; // table: root(1D), 2D不方便對照
    vector<int> size;
// !!! class 預設是private, 記得public(否則regular func call不到)
public:
    // instance & initial
    DSU(int n) {
        parent.resize(n); // !記得resize分配空間, 否則後面會越界error!
        size.resize(n, 1); // 初始化 size = 1;

        for (int i = 0; i < n; i++) {
            parent[i] = i; // 初始化root都是自己(各自獨立的島)
        }
    }
    // helper: find() & unite()
    int find(int uniId) {
        if (parent[uniId] != uniId) {
            parent[uniId] = find(parent[uniId]);
        } else {return uniId;}
        return parent[uniId];
    }

    bool unite(int uniIdA, int uniIdB) { // check: if isn't the same island, then unite.
        int pA = find(uniIdA), pB = find(uniIdB); // find roots
        if (pA == pB) {
            return false; // same island ->> do nothing & retrun false;
        } else {
            // unite by size
            if (size[pA] < size[pB]) {
                swap(pA, pB); // 記得交換後, 下面更新的實際情況
            }
            parent[pB] = pA; // 小歸類在大的下面(可能讓層級較少 & node變動較少)
            size[pA] += size[pB];
            
            return true;
        }
    }
};

class Solution {
public:
    // shared initial, container
    int ROWS, COLS;
    // regular func
    int numIslands(vector<vector<char>>& grid) {
        // 1.initial
        ROWS = (int)grid.size(), COLS = (int)grid[0].size();
        int n = ROWS * COLS;
        DSU dsu(n);

        vector<pair<int, int>> directions = { // up & left(2 only): avoid duplicated check
            {-1, 0}, {0, -1}
        };
        int island = 0;
        // 2.Traverse the grid(double for loop): find the start '1'
        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
            // (1)if (is island '1') 
                if (grid[r][c] == '1') {
                    island++;
                // (2) for 2 directions {if (is island '1' && inbound) {check (unite()) {island++/--;}}}
                    for (auto& [dr, dc] : directions) {
                        int nR = r + dr, nC = c + dc;
                        if (nR >= 0 && nC >= 0 && nR < ROWS && nC < COLS &&
                            grid[nR][nC] == '1') {
                            // 直接call dsu.unite(): 包含find root & compare wether the same island info. (記得寫helper)
                            if (dsu.unite(toUniId(r, c), toUniId(nR, nC))) { // true: 不同island造成合併
                                island--; // 因為合併 ->> 一開始+的要-回來!
                            }
                        }
                    }
                }
            }
        }
        // 3.return: After processing all cells, the remaining count is the number of islands.
        return island;
    }
    // helper
private:
    int toUniId(int row, int col) {
        return row*COLS + col; // 0-based
    }
};



// int main() {
//     Solution sol;
//     vector<vector<char>> grid = {
//         {'1', '1', '0', '0', '0'},
//         {'1', '1', '0', '0', '0'},
//         {'0', '0', '1', '0', '0'},
//         {'0', '0', '0', '1', '1'}
//     };
//     cout << "Input grid:" << endl;
//     for (const auto& row : grid) {
//         for (char cell : row) {
//             cout << cell << " ";
//         }
//         cout << endl;
//     }

//     int numIslands = sol.numIslands(grid);
//     cout << "Number of islands: " << numIslands << endl; // Output: 3
//     return 0;
// };