
// clang++ .\Test.cpp -std=c++17 -o Test.exe
// .\Test.exe

// #include <iostream>
// #include <vector>

// using namespace std;


/*
 [題目理解]
    # Return: 
        - the ordering of courses(If there are many valid answers, return any of them.)
        - If it is impossible to finish all courses, return an empty array.
    # note:
        - 0 <= prerequisites.length <= numCourses * (numCourses - 1)
        - prerequisites[i].length == 2
        - All the pairs [ai, bi] are distinct.
        - ai != bi
    # thoughts:
        1.延續 207. Course Schedule, 原本是return boolean ->> II 要return path order!
*/


/*
 一、[2. Topological Sort (Kahn's Algorithm)]
    T:  O(V + E).
        O(E) for prerequisites for loop
        O(V) for traversing the indegree(numCourses)
        O(V) for while loop(outter): get & push
        O(E) for while loop(inner loop in total)
    S:  O(V + E).
        O(V) for queue
        O(V) for indegree
        O(E) for next
    (Where V is the number of courses and E is the number of prerequisites.)

    # thoughts:
        1. 先抓住一句話：「某件事必須先完成，另一件事才能做」→ 有先後依賴關係 → 想到有向圖。
        2. 接著，題目要求「排出完成所有事情的順序」，因此想到 拓樸排序（Topological Sort）。
        3.
                思考問題	        這題的答案             對應程式
            現在能先修哪門課？	沒有尚未完成的先修課	indegree[i] == 0
            修完它會影響誰？	需要它當先修課的課程	adj[i]
            怎麼記錄目前能修的課？	放進等待處理的容器	queue<int>
*/

// class Solution {
// public:
//     // shared container, initial
//     // regular
//     vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
//         // 1.initial: (1)finish, output (2)build indegree, next (3)push the proper courses into queue
//         int finish = 0;
//         vector<int> res;
//         queue<int> noPreQ;
//         vector<int> indegree(numCourses, 0);
//         vector<vector<int>> next(numCourses, vector<int>{}); // vector<vector<int>> next(numCourses); 也行 

//         for (auto& p : prerequisites) {
//             indegree[p[0]]++; // 目標課對應的先修數++
//             next[p[1]].push_back(p[0]); // 先修課可能解鎖的課
//         }
//         for (int i = 0; i < numCourses; i++) {
//             if (indegree[i] == 0) {
//                 noPreQ.push(i);
//             }
//         }

//         // 2.while (queue is not empty())
//         while (!noPreQ.empty()) {
//             // (1)get & pop each course, then traversing each next[course]: 
//             int noPreC = noPreQ.front(); noPreQ.pop();
//             finish++;
//             res.push_back(noPreC);
//             // (2)update: indegree(by check up in next)
//             for (auto& c : next[noPreC]) {
//                 // (i)if (indegree == 0); then push into queue
//                 indegree[c]--; // 修完課, 先減再檢查! 記得更新: 目標課的先修課數!!!
//                 if (indegree[c] == 0) {
//                     noPreQ.push(c);
//                 }
//             }
//         }
//         // 3.out of while loop: check finished == numCourses ? return output : return []
//         if (finish == numCourses) {
//             return res;
//         }
//         return {};
//     }
// };




/*
 二、[1. Cycle Detection（DFS）]
    T:  O(V + E).
        O(E) for traversing prerequisites to push
        O(V + E) for traversing numCourses & recursion(dfs): 全部 DFS 合計
            雖然外層對每門課都呼叫 DFS，但：
            - 每個節點只會完整展開一次；之後遇到 state == 2 直接回傳。
            - 每條邊只會在起點展開時檢查一次。
        O(V) for reverse res
    S:  O(V + E).
        O(V) for state
        O(V + E) for res; 即使沒有任何邊，也要建立 V 個內層 vector；所有內層 vector 再合計儲存 E 個鄰接節點
        O(E) for next 
        O(V) for worst-case recursion call stack(dfs)
    (Where V is the number of courses and E is the number of prerequisites.)

    # thoughts:
        1.traversing each numCourses to find whether there is a cycle?
        2.dfs
        3.stste: 0, 1, 2(尚未處理, 同dfs線進行中, 已確認所有連結路線都安全 ->> 可不必再展開)
            ->> state 
*/

// class Solution {
// public:
//     // shared container, initial:
//     vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
//         // 1.initial: res, state, next (state找cycle ->> 取代indegree)
//         vector<vector<int>> next(numCourses); // 注意: 必須先給範圍大小(因為後面會指定[] ->> 抓不到位置)
//         vector<int> res; // 必須為空 ->> 避免後面push_back, 多了很多0
//         vector<int> state(numCourses, 0);

//         for (auto& p : prerequisites) {
//             next[p[1]].push_back(p[0]);
//         }
//         // 2.traversing each numCourses
//         for (int i = 0; i < numCourses; i++) {
//             // (1)if (call dfs(int course) == has cycle) {return {};}
//             if (!dfs(i, res, state, next)) {
//                 return {};
//             }
//         }
//         // 3.out of loop ->> no any cycle
//         reverse(res.begin(), res.end()); // 注意push順序!!!
//         return res;
//     }
// private:
//     // helper- dfs
//     bool dfs(int course, vector<int>& res, vector<int>& state, vector<vector<int>>& next) {
//         // 1.initial:
//         // 2.if (state == 1)
//         if (state[course] == 1) {
//             return false; // cycle
//         }
//         // 2.if (ststae == 2)
//         if (state[course] == 2) {
//             return true; // 確保之後展開所有都沒cycle問題!
//         }
//         // 3.update state & start traversing each next[course]
//         state[course] = 1; // 能進到這, 代表非 1, 2 ->> 必定是 0
//         for (auto n : next[course]) { // int 不要用& !!!
//             // (1)if (each of next[course] has cycle) {return false;}
//             if (!dfs(n, res, state, next)) {
//                 return false; // 有環
//             }
//         }
//         // 4. out of loop: otherwise: pass(no cycle), update state & push to res & return true;
//         state[course] = 2; // 能到這, 代表全部都確認no cycle ->> 此課安全
//         res.push_back(course);

//         return true;
//     }
// };



/*
 三、[3. Topological Sort (DFS)]
    T:  O(V + E).
        O(E) for traversing prerequisites
        O(V) for traversing numCourses and push into start
        O(V + E) total for (int s : start) and call dfs recursion 
    S:  O(V + E).
        O(V) for indegree
        O(V + E) for next(outter + inner)
        O(V) for worst-case start
        O(V) for worst-case call stack(dfs)
    (Where V is the number of courses and E is the number of prerequisites.)

    # thoughts:
        1.方法一、Topological Sort (Kahn's Algorithm) 使用 BFS ->> 此方法用DFS
        2.Topological Sort（DFS）：用遞迴處理「剛解鎖的課程」。
            ->> 可以從 Kahn 改寫來理解。
            ->> Kahn 修完一門課後，會更新後續課程：
                indegree[c]--;

                if (indegree[c] == 0) {
                    noPreQ.push(c);  // 已經可以修，先排隊
                }

            ->> 第三種把「先排隊」改成「立刻遞迴處理」：
                indegree[c]--;

                if (indegree[c] == 0) {
                    dfs(c);         // 已經可以修，立刻處理
                }
            ->> 所以它仍然需要 indegree，不需要三色 state。
        3. 第三種是「確定能修才進入，進入就記錄」，因此直接得到修課順序，不需要反轉。
        4.這只是其中一種合法的修課排序。
            ->> 也可以先把所有「一開始不需要先修課」的課程排在 res 前段。
            ->> 因為這些課程彼此沒有先修依賴，所以它們之間可以任意排序。(非標準直覺排序)
*/

class Solution {
public:
    // regular func
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        // 1.initial: res, indegree, next
        vector<int> res;
        vector<int> indegree(numCourses, 0);
        vector<vector<int>> next(numCourses, vector<int> {});

        for (auto& p : prerequisites) {
            indegree[p[0]]++;
            next[p[1]].push_back(p[0]);
        }
        // 2.traversing all numCourses, find no pre courses and push into start as startings;
        vector<int> start;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                start.push_back(i);
            }
        }
        // 3.traversing all startings, then call helper func- dfs(to collect the res)
        for (int s : start) {
            dfs(s, res, indegree, next);
        }
        // 4.out of above, compare res.size() == numCourses ?
        if ((int)res.size() == numCourses) {
            return res;
        } else {
            return {};
        }
    }
private:
    // helper- dfs
    void dfs(int course, vector<int>& res, vector<int>& indegree, vector<vector<int>>& next) {
        // 1.initial
        // 2.push course into res
        res.push_back(course); // 用res.size() 就不用 int finish
        // 3.travesing each n : next[course]
        for (int n : next[course]) {
            // (1)update: indegree
            indegree[n]--;
            // (2)if (n has no pre course) {call dfs} ->> 代表直接繼續下去
            if (indegree[n] == 0) {
                dfs(n, res, indegree, next);
            }
        }
    }
};



// int main() {
//     Solution sol;
    
//     vector<vector<int>> prerequisites = {{1, 0}, {2, 0}, {3, 1}, {3, 2}};
//     cout << "[prerequisites]: ";
//     for (const auto& p : prerequisites) {
//         cout << "[" << p[0] << ", " << p[1] << "] ";
//     }
//     cout << endl;

//     int numCourses;
//     cout << "[input numCourses]: "; cin >> numCourses; cout << endl;

//     vector<int> order = sol.findOrder(numCourses, prerequisites);

//     if (!order.empty()) {
//         const char* separator = "";
//         cout << "[Course order]: {";
//         for (int course : order) {
//             cout << separator << course;
//             separator = ", ";
//         }
//         cout << "}" << endl;
//     } else {
//         cout << "[It is impossible to finish all courses.]" << endl;
//         cout << "{";
//         const char* separator = "";
//         for (auto course : order) {
//             cout << separator << course;
//             separator = ", ";
//         }
//         cout << "}" << endl;
//     }

//     return 0;
// }