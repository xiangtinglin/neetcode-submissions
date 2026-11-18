// clang++ .\Test.cpp -std=c++17 -o Test.exe
// .\Test.exe

// #include <iostream>
// #include <vector>
// #include <unordered_map>

// using namespace std;

/*
 【題目理解】
    # Sol:
        1.暴力法：產生重複路徑，再用 set 去重。
        2.Backtracking：在「不選分支」一次跳過相同數字。
        3.Backtracking(Optimal): 
            不再問「這個 index 選不選」
            直接用 for 迴圈問「下一個要選誰」
            並在同一層跳過相同數值
        4.
*/

/*
 一、[Brute Force]
    T:  O(n log n) for sort() + O(n^2 * n) = O(n * 2^n)
        最多 2ⁿ 個子集合(總node = 2^0 + 2^1 + ... + 2^n = 2^n+1 - 1 = 2 * 2^n - 1 < 2 * 2^n) = 2^n 
        × 
        每個子集合最多.insert()複製 O(n) 個元素

    S:  O(n * 2^n): including output space
        O(n): for extra space; worst height(call stack): n, curV worst: n

*/

// class Solution {
// public:
//     set<vector<int>> res;

//     vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
//         sort(candidates.begin(), candidates.end()); // 插入 set 前，要先把答案排序成統一形式，否則 [2,1,2] 與 [1,2,2] 會被視為不同答案。
//         res.clear(); // 保險防呆
//         vector<int> curV; // 之後不用.clear() ->> 區域變數, 每次呼叫 combinationSum2()，都會重新建立一個全新的空 curV
//         dfs(candidates, target, 0, curV);
//         return vector<vector<int>>(res.begin(), res.end()); // 記得轉型
//     }

//     void dfs(vector<int>& candidates, int remaining, int startIndex, vector<int>& curV) {
//         if (remaining == 0) {
//             res.insert(curV); // set用.insert(), vector用.push_back()
//             return; // 
//         }
//         if (startIndex >= (int)candidates.size() || candidates[startIndex] > remaining) {
//             return; // early stop: candidates[startIndex] > remaining 只有在陣列已排序時才可以直接 return
//         }
//         curV.push_back(candidates[startIndex]);
//         dfs(candidates, remaining - candidates[startIndex], startIndex + 1, curV); // 不是startIndex, 因為這題不能重複使用同一個數字
//         curV.pop_back();
//         dfs(candidates, remaining, startIndex + 1, curV);
//     }
// };


/*
 二、[Backtracking]
    T:  O(n * 2^n) for total.
        1. O(n log n) for sort()
        2. O(2^n) for recursion(most nodes) + O(n * 2^n) for worst push_back = O(n * 2^n)
        most nodes: O(2^n+1 - 1) = O(2 * 2^n - 1) = O(2^n)
        most subset: O(2^n)
        worst push: O(n)

    S:  O(2n) = O(n) for extra.
        1. O(n) for worst call stack
        2. O(n) for worst curV

    # thoughts:
        1.暴力解用 set 去重複: 但是還是重複走
            ->> 避免重複走也就能不用 set: 分支為不選的某些情況需要排除(pruning)
            ->> 數值有重複者持續跳過, 直到獨一數字才處理(進去不選recursion): 避免重複排列組合
*/

// class Solution {
// public:
//     vector<vector<int>> res; // helper要用 ->> 需外部宣告; 不用set, 因為此法會pruning不走重複路徑

//     vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
//         res.clear(); // 若多次call func, 記得防呆
//         // 1.sort: for pruning
//         sort(candidates.begin(), candidates.end());
//         // 2.call helper func
//         vector<int> curV;
//         dfs(candidates, target, 0, curV);
//         // 3.return
//         return res;
//     }

// private:
//     // helper
//     void dfs(vector<int>& candidates, int remaining, int startIndex, vector<int>& curV) {
//         if (remaining == 0) {
//             res.push_back(curV); // set 用insert, vector用 push_back!
//             return; // 因已排序, 找到後就回上層, 避免繼續走進入多餘錯誤計算
//         }
//         if (startIndex >= (int)candidates.size() || candidates[startIndex] > remaining) {
//             return; // 此層已不可能 ->> 提早pruning
//         }
//         // 分支: 選
//         curV.push_back(candidates[startIndex]); // 記得先push!
//         dfs(candidates, remaining - candidates[startIndex], startIndex + 1, curV); // i + 1
//         // 分支: 不選
//         curV.pop_back(); // 記得撤回!
//         while ((startIndex + 1) < (int)candidates.size() && candidates[startIndex] == candidates[startIndex + 1]) {
//             startIndex++;
//         }
//         dfs(candidates, remaining, startIndex + 1, curV); // i + 1
//     }
// };


/*
 三、[Backtracking(Optimal)]
    T:  O(n * 2^n) for total.
        O(n log n) for sort()
        O(n * 2^n) for loop & recursion
    S:  O(n) for extra.

    # thoughts:
        1.Optimal 版本不是換一個新演算法，而是把「選／不選」的二元決策，改寫成「下一個要選誰」
        2.目的都是要找下一個選誰: 從每次選不選 ->> 變成for loop決定選誰
*/

// class Solution {
// public:
//     vector<vector<int>> res;

//     vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
//         res.clear(); // 防呆多次call
//         // 1.sort: for pruning
//         sort(candidates.begin(), candidates.end());
//         // 2.call helper func
//         vector<int> curV;
//         dfs(candidates, target, 0, curV);
//         // 3.return
//         return res;
//     }

// private:
//     // helper
//     void dfs(vector<int>& candidates, int remaining, int startIndex, vector<int>& curV) {
//         if (remaining == 0) {
//             res.push_back(curV);
//             return;
//         }
        
//         // for loop: 檢查去重複
//         for (int j = startIndex; j < (int)candidates.size(); j++) {
//             // 同層的同數值可能展開重疊的組合 ->> 只展開第一個
//             if (j > startIndex && candidates[j] == candidates[j - 1]) { // 不要寫 while !
//                 continue; // 不能只 j++, 否則會繼續走. contitnue會自動下一圈 j++
//             }
//             if (candidates[j] > remaining) {break;} // 提早break;
//             // 分支- 選
//             curV.push_back(candidates[j]);
//             dfs(candidates, remaining - candidates[j], j + 1, curV);
//             curV.pop_back(); // 關鍵: 前一行dfs()已經push完match組合, 若有break回上一層執行pop ->> 代表會超過不符合 ->> 下一個loop前撤回, for loop繼續 j++ (等於跳過當前數值)
//             // 分支- 不選: 不用call ->> 因for loop(包含不選, 因j++只會往右) & while判斷(已去重)
//         }
//     }
// };



/*
 四、[Backtracking (Hash Map)
 ]
    T:  O(n * 2^n) for total.
        O(2 * 2^n) = O(2^n) worst for recursion dfs X O(n) ->> 把找到答案時複製 curV 的成本也算進去.
        O(n) for 建立 map count
    S:  O(n) for extra.(each call stack, vector, hash map)

    # thoughts:
        1.跟之前寫法不同, 用hash map紀錄 [int : freqency] ->> 不再把相同數字視為不同 index，而是壓縮成「數值＋可用次數」。
        2.Hash Map 版本重新回到二選一: 選or不選
        3.沒有 set ->> 創建唯一數值vector<int> nums;
        4.同一組數字不可能有兩種不同的使用次數表示。
            ->> 因此，只要 DFS 對每種數值依固定順序決定使用幾次，就不會產生重複答案。
        5.哪些設計共同保證不重複？不是單獨某一行，而是以下三個條件共同保證：
            相同數字壓縮成一種, 數值按固定順序處理, i 永遠不往回
        6.Hash Map 寫法不是任意挑選，而是：
            先決定使用幾個 nums[0]
            再決定使用幾個 nums[1]
            再決定使用幾個 nums[2]
            ->> 因此不會產生不同排列。
        7.相同數值合併成 count
            ＋
            每種數值只處理一次
            ＋
            依固定方向移動 i
            ＋
            每個使用次數只產生一條路徑
*/

class Solution {
public:
    // 創建container
    vector<vector<int>> res;
    unordered_map<int, int> count;

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> curV; // 每次call都會重新創建(不用clear)
        vector<int> uniV;
        res.clear();
        count.clear();
        // 1.count map & uniV
        for (int i = 0; i < (int)candidates.size(); i++) {
            if (count.find(candidates[i]) == count.end()) {
                uniV.push_back(candidates[i]);
            }
            count[candidates[i]]++;
        }
        // 不用sort!因為uniV無重複, 且接下來helper index不往回走
        // 2.執行helper- dfs
        dfs(uniV, target, 0, curV);
        // 3.return
        return res;
    }

private:
    // helper
    void dfs(vector<int>& uniV, int remaining, int startIndex, vector<int>& curV) {
        if (remaining == 0) {
            res.push_back(curV);
            return;
        }
        if (startIndex >= (int)uniV.size()) { // 沒sort, 不能用 uniV[startIndex] > remaining 判斷
            return;
        }
        // 不回頭
        int curNum = uniV[startIndex];
        // 分支1- 選
        if (count[curNum] > 0 && curNum <= remaining) { // !!!不能寫 curNum < remaining ->> 會漏掉!
            curV.push_back(curNum);
            count[curNum]--;
            dfs(uniV, remaining - curNum, startIndex, curV);

            curV.pop_back(); // 記得復原
            count[curNum]++;
        }
        // 分支2- 不選
        dfs(uniV, remaining, startIndex + 1, curV);
    }
};


// int main() {
//     Solution sol;

//     vector<int> candidates;
//     cout << "Enter candidates (space-separated): ";
//     for (int num; cin >> num;) {
//         candidates.push_back(num);
//         if (cin.peek() == '\n') break; // Stop reading when a newline is encountered
//     }

//     int target;
//     cout << "Enter target: ";
//     cin >> target;
    
//     vector<vector<int>> result = sol.combinationSum2(candidates, target);

//     // Print the result
//     for (const auto& combination : result) {
//         cout << "[";
//         for (size_t i = 0; i < combination.size(); ++i) {
//             cout << combination[i];
//             if (i < combination.size() - 1) {
//                 cout << ", ";
//             }
//         }
//         cout << "]" << endl;
//     }

//     return 0;
// }