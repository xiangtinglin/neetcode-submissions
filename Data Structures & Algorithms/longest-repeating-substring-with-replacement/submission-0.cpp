/*
Ctrl + Shift + B：只編譯

clang++ -std=c++17 Test.cpp -o Test.exe
.\Test.exe

*/

// #include <iostream>
// #include <unordered_map>
// #include <unordered_set>

// using namespace std;


/*
    1. Given: string "s", int "k"
    2. Operation: choose any character and change it to any other uppercase English character.(at most k times)
    3. Return: length of the longest substring containing the same letter you can get after performing the above operations.

    # 解題關鍵: len(window) - max_frequency(char) <= k
*/

/*
    1. Brute Force- T:O(n^2); S:O(m)
        Where:
            n is the length of the string and 
            m is the total number of unique characters in the string.

        # 核心概念: 
            1.列舉所有可能 2.HashMap- {"char": int fequency}
        ex.
            s = "ABACA"
                   j = 0, 1, ...
            i = 0, ["A", "AB", "ABA", ...]
            i = 1, ["B", "BA", "BAC", ...]
                ...    
*/

// class Solution {
// public:
//     int characterReplacement(string s, int k) {
//         unordered_map<char, int> charFreMap; // type不是string, 是char!
//         int res = 0;

//         for (int i = 0; i < s.size(); i++) {
//             charFreMap.clear(); // 每輪重新計算
//             int maxF = 0;
//             for (int j = i; j < s.size(); j++) { // 從i開始
//                 charFreMap[s[j]]++; // 先+完&記錄, 再檢查
//                 maxF = max(maxF, charFreMap[s[j]]);

//                 if ((j - i + 1) - maxF <= k) { 
//                     res = max(res, j - i + 1);
//                 }
//             }
//         }
//         return res;
//     }
// };


/*
    2. Sliding Window- T:O(m * n); S:O(m)
        Where:
            n is the length of the string and 
            m is the total number of unique characters in the string.
        # 核心: (1)不回頭 (2)不列舉所有組合 -> 一一排查能replace的選擇(s的成員) -> Hash Set -> 不用map
        
*/

// class Solution {
// public:
//     int characterReplacement(string s, int k) {
//         int res = 0;
//         unordered_set<char> charSet(s.begin(), s.end()); // 記得 (s.begin(), s.end()) !!!

//         for (char c : charSet) { // 一一排查能replace的選擇(s的成員), 不是c : s !!!
//             int cnt = 0;
//             int l = 0;

//             for (int r = 0; r < s.size(); r++) {
//                 if (s[r] == c) {cnt++;}

//                 while ((r - l + 1) - cnt > k) {
//                     if (s[l] == c) {cnt--;} // 記得移除"前"檢查【s[l]】是否cnt--(不是 s[r]!!!)
//                     l++;
//                 }
//                 res = max(res, r - l + 1);
//             }
//         }
//         return res;
//     }
// };


/*
    3. Sliding Window(Optimal)- T:O(n * m); S:O(m)
        # 核心: 方法 3 的 optimal 在於：
            方法 2 對每個目標字元 c，各自重跑一次 Sliding Window；方法 3 用頻率表同時考慮所有目標字元，因此整個字串只需掃一次。 -> HashMap

*/

class Solution {
public:
    int characterReplacement(string s, int k) {
        unordered_map<char, int> charMap;
        int res = 0;
        int maxF = 0;
        int l = 0;

        for (int r = 0; r < s.size(); r++) {
            charMap[s[r]]++;
            maxF = max(maxF, charMap[s[r]]);

            while ((r - l + 1) - maxF > k) {
                charMap[s[l]]--;
                l++;

                maxF = 0; // 更新前必須先歸0 !!!
                for (const auto& [ch, f] : charMap) {
                    maxF = max(maxF, f);
                }; // 更新當前正確window的maxF(!!!這裡不更新也不會錯 -> 難理解)
            }
            res = max(res, r - l + 1);
        }
        return res;
    }
};


// int main() {
//     Solution solution;
//     string s; cout << "Input(ex. \"AABB\"): "; cin >> s; // Input:
    
//     int k; cout << "Input(ex. 2): "; cin >> k; // Input:
    
//     int result = solution.characterReplacement(s, k);
//     cout << "Result: " << result << endl; // Output: 
//     return 0;
// }