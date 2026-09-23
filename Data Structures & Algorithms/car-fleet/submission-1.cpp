/*
Ctrl + Shift + B：只編譯

clang++ -std=c++17 Test.cpp -o Test.exe
.\Test.exe
*/

// # include <iostream>
// # include <vector>
// # include <algorithm> // sort
// # include <utility> // pair
// # include <stack>
// using namespace std;

/*
# 限制:
    1. A car cannot pass another car
    2. if catch up -> at the speed of the slower car(same fleet)
    3. The speed of the car fleet is the minimum speed of any car in the fleet. -> 只要看最右邊"必"最慢
    4. Return: the number of car fleets that will arrive at the destination.

# 核心概念:
    1. Pair: (Position, Speed) & 排序
    2. 右 -> 左 & 計算各別到Traget所需time -> 判斷會不會collision
# 作法:
    Iteration 更精簡，而且不需要額外保存所有 fleet time
*/

/*
一、Stack- T:O(n log n); S:O(n)
    # 概念:
        1. Pair: (Position, Speed) & 排序
        2. 右 -> 左 & 計算各別到Traget所需time -> 判斷會不會collision
        3. 用Stack紀錄fleet情況 -> if not collision -> .push() 反之 .pop()
        4. 其他:「Stack 解題思維」≠「一定要使用 std::stack」
*/

// class Solution {
// public:
//     int carFleet(int target, vector<int>& position, vector<int>& speed) {
//         int n =static_cast<int>(position.size());
//         // (1)先建立pair
//         vector<pair<int, int>> psPair;
//         for (int i = 0; i < n; i++) {
//             psPair.push_back({position[i], speed[i]}); // pair要{}!!!
//         }
//         sort(psPair.rbegin(), psPair.rend()); // r: reverse, 由大到小; sort 預設先看 pair.first
//         vector<double> stack; // vector模擬stack -> 因需用index[]; 一般小數計算→ double精度更高
//         for (const auto& p : psPair) { // &: reference避免不必要的 copy
//             stack.push_back(static_cast<double>(target - p.first) / p.second); // int除法小數被截掉 & stack是double
//             int stackSize = static_cast<int>(stack.size());
//             if (stackSize >= 2 && // 用if不用while -> 越接近target的, 先前已檢查過(不能超越前車) -> 不用重複判斷
//                 stack.back() <= stack[stackSize - 2]) { // C++的vector不支援負數index
//                 stack.pop_back();
//                 }
//         }
//         return static_cast<int>(stack.size());
//     }
// };


/*
二、No.1 Iteration- T:O(n log n); S:O(n)
    # 首選原因: Iteration 更精簡，而且不需要額外保存所有 fleet time

    # 核心概念: 計算各別car到target的time -> 不用stack依序比較
    # 流程:
        1. sorting: from closest to the target to farthest
        2. calculate- new fleet: only if it takes longer than the fleet in front of it.
        3. not using a stack: keep track of the most recent fleet time.
*/

class Solution {
public:
    int carFleet(int& target, vector<int> position, vector<int> speed) {
        vector<pair<int, int>> pair;
        int n = static_cast<int>(position.size());
        for (int i = 0; i < n; i++) {
            pair.push_back({position[i], speed[i]});
        }

        sort(pair.rbegin(), pair.rend());

        int fleet = 1;
        double prevT = static_cast<double>(target - pair[0].first) / pair[0].second;

        for (int i = 1; i < n; i++) {
            double currT = static_cast<double>(target - pair[i].first) / pair[i].second;
            if (currT > prevT) {
                fleet++;
                prevT = currT;
            }
            // otherwise: 什麼都不做
        }
        return fleet;
    }
};

// int main() {
//     Solution solution;
//     int target = 12;
//     vector<int> position = {5, 1, 1, 3, 10, 8, 7, 6, 2, 4};
//     vector<int> speed = {2, 4, 1, 1, 3, 2, 1, 3, 2, 4};
//     int result = solution.carFleet(target, position, speed);
//     cout << "Number of car fleets: " << result << endl; // Output: Number of car fleets: 3
//     return 0;
// }
