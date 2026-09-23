// # include <iostream>
// # include <vector>

// using namespace std;

/*
1️⃣ Brute Force- T:O(n^2); S:(n)
*/

// class Solution {
// public:
//     vector<int> dailyTemperatures(vector<int>& temperatures) {
//         int n = static_cast<int>(temperatures.size());
//         vector<int> ans(n, 0); // ⚠️務必初始化, 否則容器中沒東西用[index]會出錯

//         for (int i = 0; i < n; i++) {   
//             for (int j = i + 1; j < n; j++) {
//                 if (temperatures[i] < temperatures[j]) {
//                     ans[i] = j - i; // 不用cnt慢慢加
//                     break; // ⚠️務必break❗️否則後續會覆蓋
//                 }
//                 // 若都沒更大, 維持初始0
//             }
//         }
//         return ans;
//     }
// };

/*
3️⃣ Dynamic Programming- 
T:O(n) // 題目有限制 30 <= t[i] <= 100, 最多O(71 * n)。 每個 i 真的都跳接近 n 次 -> 假設不可能成立!
S:
O(1) extra space.
O(n) space for the output array.

    目前問題：計算 res[i]
    已解子問題：右側的 res[j]
    重複利用：透過 j + res[j] 跳到已知位置
*/
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = static_cast<int>(temperatures.size());
        vector<int> res(n, 0);

        for (int i = n- 2; i >=0; i--) {
            int j = i + 1;
            while (j < n && (temperatures[i] >= temperatures[j])) { // 一直while loop直到結束or找到更大
                if (res[j] == 0 ) {
                    j = n; // ⚠️ 必須要->「表示找不到」的標記, & 防止執行後續if
                    break;
                }
                j += res[j]; // 跳到下一個更大的數index -> 繼續比較
            }
            if (j < n) { // 用j = n or j < n, 判斷是否找到更大
                res[i] = j - i;
            }
        }
        return res;
    }
};


// int main() {

//     vector<int> nums_1 = {0, 2, 2 ,7, 11, 15};
//     vector<int> nums_2 = {1, 3, 6, 10};

//     Solution sol;
//     vector<int> res_1 = sol.dailyTemperatures(nums_1);
//     vector<int> res_2 = sol.dailyTemperatures(nums_2);

//     cout << "res_1: ";
//     for (int x : res_1) {
//         cout << x << " ";
//     }
//     cout << endl;

//     cout << "res_2: ";
//     for (int x : res_2) {
//         cout << x << " ";
//     }
//     cout << endl;

//     return 0;
// }