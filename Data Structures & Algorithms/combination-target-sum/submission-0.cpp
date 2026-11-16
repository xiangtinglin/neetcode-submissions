/*
 [題目理解]
    # Given: an array(distinct integers) candidates and a int targe.
    # Return: combinations(any order, can be chosen unlimited number of times.)
    # note:
        1.Two combinations are unique: if the frequency is different.
        2.All elements of candidates are distinct.
    # Requirement:
        1.系統性地產生所有不重複組合。
        2.判斷避免重複組合.
    # Sol:
        方法一：理解遞迴決策樹
           ↓
        方法二：將多個選擇整理成 for loop
                ↓
        加入排序與 pruning
*/

/*
一、【Backtracking】
    T:O(2 ^ (t/m)), where t/m is the height of recursion
    S:O(2 * t/m) = O(t/m)
    (Where t is the given target and m is the minimum value in nums.)

    # thoughts:
        1.Core: 
            核心不是「怎麼湊出 7」，而是：如何系統性列舉所有組合，同時允許重複使用數字，又不產生 [2,3,2]、`[3,2,2]` 這類重複排列?
            (1)最直覺的暴力想法:
                第一層：選 2、3、6、7
                第二層：再選 2、3、6、7
                ...
            ->>問題: 如何避免重複組合？ ->> 需要限制「接下來可以選哪些數字」
            ->>規定：一旦選了某個位置的數字，之後只能選目前位置或右邊的數字，不能再回頭選左邊。
                ex. 
                    [2,2,3]  可以產生
                    [2,3,2]  不會產生，因為選完 3 不能回去選 2
                ex. nums = [2,3,6,7], target = 7   
                                  
                              分支(1)加當前數字                  分支(2)不加
                                                    []
                                [2]                                   []
                    [2,2]               [2]                [3]                  []
            [2,2,2]     [2,2]     [2,3]     [2]     [3,6]       [3]      [6]           []    
                     [2,2,3]  [2,3,6] [2,3]
*/


// class Solution {
// public:
//     // 1.Initial
//     vector<vector<int>> res;
    
//     vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
//         vector<int> tmpV;
//         // 2.helper- dfs(candidats, target, ,)
//         dfs(candidates, target, 0, tmpV); // index, remaining
//         return res;
//     }

//     void dfs(vector<int>& candidates, int remaining, int index, vector<int> tmpV) {
//         // 1.找到 
//         if (remaining == 0) {
//             res.push_back(tmpV);
//             return; // 記得return! 否則會繼續下去!!!
//         }
//         // 2.超過boundary, 停止繼續 ->> trace back
//         if (index >= (int)candidates.size() || remaining < 0) {
//             return;
//         }
//         // 3.開始開展recursion
//         // (1)分支- 先處理要加入當前數字
//         tmpV.push_back(candidates[index]); // 選
//         dfs(candidates, remaining - candidates[index], index, tmpV); // index不用 + 1
//         // (2)分支- 也要處理不加入當前數字路徑
//         tmpV.pop_back(); // 撤銷選擇(記得到底回傳到頂後, 最原始被push的第一個數字, 要pop掉!)
//         dfs(candidates, remaining, index + 1, tmpV); // 不選!(remaining傳入, 後續逐層再按分支處理)
//         // 處理後不用return什麼
//     }
// };


/*
二、【Backtracking (Optimal)】
    T: O(n^D) for 寬鬆上界 + O(n log n) for sort() = O(n^D + nlogn)
    S: O(2 * (t/m)) = O(t/m) for recursion call stack & curV(要用&共用, 否則每次都會複製).
    where:
        n = candidates.size()
        t = target
        m = candidates 中最小的數字
        D = t / m

    # thoughts:
        1.avoids exploring useless paths by using sorting + early stopping.
        2.方法二不是為了避免重複而必須排序；排序主要是為了提早剪枝。
        --> 方法一大量使用 dfs(i + 1) 逐個跳過候選數字，因此可以把「這一層要選哪個候選數字」集中交給一個 for loop 處理。
*/

class Solution {
public:
    // initial
    vector<vector<int>> res;
    vector<int> curV;

    // 主方法函式
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        // 1.sort: 方便辨別重複組合 & early stoping!
        sort(candidates.begin(), candidates.end());
        // 2.call helper function: 設計需要傳入什麼參數
        dfs(candidates, target, 0, curV); // candidates, remaining, start index, curV
        // 3.return
        return res;
    }

    // helper
    void dfs(vector<int>& candidates, int remaining, int start, vector<int>& curV) {
        // 1.if 判斷式: match & push
        if (remaining == 0) {
            res.push_back(curV);
            return; // 後面層都會超過! ->> 回上層
        }
        // (if 判斷式: 回上層條件放for loop內)
        // 2.for loop: recursion執行
        for (int s = start; s < candidates.size(); s++) {
            if (candidates[s] > remaining) {break;} // 已排序 ->> 必確定: 後面層都會超過! ->> 早停!!!(不要寫 remaining < 0, 否則無效!整層remaining都一樣 ->> for loop仍跑完)

            curV.push_back(candidates[s]); // 開始分支- 依序選定
            dfs(candidates, remaining - candidates[s], s, curV);
            curV.pop_back(); // 下一個for loop要換新開頭 ->> 先pop掉當前的
        }
    }
};