// # include <iostream>
// # include <vector>

// using namespace std;

/*
# 題目:
    Given: n piles, h hours,
    變因: eating speed of k / per h
    Return: minimum int k -> eat all in h hours.
# 限制:
    1. If the pile has less than k -> not eat any more(during this hour)
    2. likes to eat slowly but still wants to finish eating all before the guards return. -> 「minimum」
# 關鍵- k(speed)的搜尋方式:
    1. 🔥k(speed) = [1, 2 ..., max(piles[i])] -> 已排好, 求最小k(最慢)
    2. hours(per pile) = (piles[i] - 1 + k) / k -> 取ceiling
    3. Total_hours <= h
*/

/*
1️⃣Brute Force- T:O(n * m); S:(1)
    Where n is the length of the input array piles and m is the maximum number of bananas in a pile.
*/

// class Solution {
// public:
//     int minEatingSpeed(vector<int>& piles, int h) {
//         int max_k = *max_element(piles.begin(), piles.end());
//         for (int k = 1; k <= max_k; k++) {
//             long long total_h = 0; // 避免溢位需要64-bit
//             for (int pile:piles) {
//                 total_h += (pile - 1 + k) / k;
//             }
//             if (total_h <= h) {
//                 return k;
//             }
//         }
//         return -1;
//     }
// };

/*
2️⃣Binary search- T:O(n * log m); S:O(1)
    # 核心概念: k(speed)的搜尋方式
*/

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int l = 1, r = *max_element(piles.begin(), piles.end());
        int res = 0;

        if (piles.size() > h) return -1;

        while (l <= r) {
            int k = l + ((r - l) / 2);
            long long totalH = 0;
            for (int pile:piles) {
                totalH += ceil(static_cast<long double>(pile) / k); // ⚠️沒有double double❗️只有long double❗️float (32-bit) 只能保證約 7 位 -> 題目Constraints要64-bit（float: 32/ double: 64/ long double: 80-bit 或 128-bit. 
            }
            if (totalH <= h) { //吃太快 -> k放慢
                res = k;
                r = k - 1;
            } else {
                l = k + 1;
            }
        }
        return res;
    }
};

// int main() {
//     vector<int> piles = {3, 6, 7, 11};
//     int h = 4;
//     Solution solution;
//     int result = solution.minEatingSpeed(piles, h);
//     cout << "Minimum eating speed: " << result << endl;
//     return 0;
// }