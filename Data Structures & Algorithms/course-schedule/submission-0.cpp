
// clang++ .\Test.cpp -std=c++17 -o Test.exe
// .\Test.exe

// #include <iostream>
// #include <vector>

// using namespace std;


/*
 [理解題目]
    # Given:
    # return: boolean
        Return true if you can finish all courses. Otherwise, return false.
    # note:
        1.prerequisites[i].length == 2
    # thoughts:
        1.關鍵: 判斷「課程依賴關係」形成的有向圖中，有沒有環（cycle）。
            - 沒有環：可以修完所有課程。
            - 有環：課程互相等待，無法修完。
            ->> 把題目轉成圖
                ex. numCourses = 2
                    prerequisites = [[1,0]]
                    0 → 1

*/

/*
 一、Topological Sort (Kahn's Algorithm)
    T:  O(V + E)
        O(V + E) for loop: initializing buiding indegree & next list
        O(V + E) for the whole while loop(outter: V; inner for loop: E for total not each for loop)
    S:  O(V + E)
        O(V + E) for indegree & next list
        O(V) for queue
    (Where V is the number of courses and E is the number of prerequisites.)

    # thoughts:
        1.建議先掌握的解法，因為它和「實際修課」的過程很接近。
            ->> 先找出：現在不需要任何先修課的課程。
            ->> 如果某門課的先修條件全部完成，它也可以加入待修清單。
                持續這個過程：
                - 如果最後修完 numCourses 門課：沒有 cycle。
                - 如果 queue 空了，卻還有課沒修完：剩下的課互相依賴，存在 cycle。
        2.關鍵概念: 
            `indegree[i]` 表示：課程 i 還有幾門先修課尚未完成。
            ex：
                0 → 1
                2 → 1
                課程 1 必須先完成 0 和 2： indegree[1] = 2;
                ->> indegree[i] == 0, 代表這門課目前不需要等待任何先修課，可以直接修。
        3.EX:
            numCourses = 4
            prerequisites = [[1,0], [2,0], [3,1], [3,2]]
            關係:
                0 → 1 → 3
                 \      ↑
                   → 2 ─┘
        4.建立 indegree
            課程 0：0 門先修課
            課程 1：1 門先修課
            課程 2：1 門先修課
            課程 3：2 門先修課         
            ->> indegree = [0, 1, 1, 2]          
*/

// class Solution {
// public:
//     bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
//         // 1.container, initial: (1)indegree[x] = course x's pre cnt(== 0, 代表可以直接修); (2)next[x] 修了x後可解鎖的課(但真的要能修, 得符合ingree[該課] == 0); (3)queue: 放可直接修的(ingree[x] == 0) (4)finished
//         vector<int> indegree(numCourses, 0); // 對應該課需要多少先修課 ->> 0代表可直接修
//         vector<vector<int>> next(numCourses);
//         queue<int> noReQ;
//         int finished = 0;
//         // 2.traversing the prerequisites to buid the indegree, next
//         for (auto& pre : prerequisites) {
//             indegree[pre[0]]++; // pre[0] is target
//             next[pre[1]].push_back(pre[0]); // push next course
//         }
//         // 3.traversing the indegree to find == 0 and push into queue
//         for (int i = 0; i < (int)indegree.size(); i++) {
//             if (indegree[i] == 0) {
//                 noReQ.push(i);
//             }
//         }
//         // 4.while (queue is not empty)
//         while (!noReQ.empty()) {
//             // (1)get and pop
//             int noReCourse = noReQ.front(); noReQ.pop();
//             // (2)update finished
//             finished++;
//             // (3)traversing each of next[x]
//             for (auto& n : next[noReCourse]) {
//                 // (i)update: indegree[next[x]]
//                 indegree[n]--;
//                 // (ii)check if (indegree[next[x]]) == 0, then push into queue
//                 if (indegree[n] == 0) {
//                     noReQ.push(n);
//                 }
//             }
//         }
//         // 5.compare finished, numCourses & return
//         return finished == numCourses;
//     }
// };



/*
 二、[Cycle Detection (DFS)]
    T:  O()
    S:  O()
    (Where V is the number of courses and E is the number of prerequisites(edge).)

    # thoughts:
        1.從BFS到DFS也能做
            BFS 的想法是： 不斷修掉目前 indegree 為 0 的課，最後看是否修完全部。
            DFS 則是： 從某門課一路查看依賴關係，如果沿著目前路徑又回到已在路徑中的課，代表有 cycle。
            ->> 從next下手, 分支往下
        2.目標: 找是否有 cycle
            需要三種狀態：
            state[course] = 0;  // 尚未檢查
            state[course] = 1;  // 正在目前 DFS 路徑中
            state[course] = 2;  // 已檢查完成，確認沒有 cycle
                ->> 不是表示：我曾經看過這個節點。
                    而是表示： 我已經從這個節點出發，完整檢查過所有能到達的路徑，而且沒有發現 cycle。
                    這比普通 visited 更強。
            ex. 
                遇到 state == 1：回到目前路徑中的節點 → cycle
                遇到 state == 2：以前已完整檢查過 → 安全
        3.Act:
            0：尚未檢查
            ↓ 進入 dfs
            1：正在目前路徑
            ↓ 所有鄰居檢查完成
            2：確認安全

*/

class Solution {
public:
    // shared container, initial: state, next(indegree就不用了)
    vector<int> state;
    vector<vector<int>> next;
    // regular func
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // 1.initial: state, next filling(traversing the prerequisites)
        state.assign(numCourses, 0); // initial在這 ->> 每次call func都能初始化reset
        next.resize(numCourses); // .assign(numCourses, {}) 也可以
        for (auto& p : prerequisites) {
            next[p[1]].push_back(p[0]); // next[p[1]] 必須已經存在 ->> 因此前面必須給範圍大小!!!
        }
        // 2.traversing each numCourses
        for (int i = 0; i < numCourses; i++) {
            // (1)if (dfs())
            if (!dfs(i)) {
                return false; // 只要任何一個是false ->> 有cycle ->> 失敗
            }
        }
        // out of loop- 都pass沒有任何cycle!
        return true;
    }

private:
    // helper- dfs
    bool dfs(int course) { // 只要傳入1個參數
        // 1.if (state[] == 1)
        if (state[course] == 1) {
            return false;
        }
        // 2.if (state[] == 2)
        if (state[course] == 2) {
            return true;
        }
        // 正式進入/繼續- 加入目前DFS path ing state
        // # update: state[] == 1
        state[course] = 1;
        // 3.traversing each next element
        for (auto& n : next[course]) {
            // (1)if (!dfs())
            if (!dfs(n)) {
                return false;
            }
        }
        // # 記得backtracking(但不是撤回) ->> 離開目前 DFS path，並標記為已確認安全(不是改回 state[course] = 0;)
        state[course] = 2; // 走到這代表前面都沒false! ->> 檢查通過, 永久標記
        
        return true;
    }
};



// int main() {
//     Solution s;
//     vector<vector<int>> prerequisites = {{1,0}, {2,0}, {3,1}, {3,2}};
//     cout << "Input: prerequisites = [[1,0],[2,0],[3,1],[3,2]]" << endl;
    
//     int numCourses;
//     cout << "Enter the number of courses: "; cin >> numCourses; // Input: 4
    
//     bool result = s.canFinish(numCourses, prerequisites);
//     cout << (result ? "true" : "false") << endl; // Output: true
//     return 0;
// }