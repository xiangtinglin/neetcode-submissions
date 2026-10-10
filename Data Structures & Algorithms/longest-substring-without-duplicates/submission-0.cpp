// clang++ -Wall -Wextra -Werror -std=c++17 -o Test_string Test_string.cpp

// #include <iostream>
// #include <unordered_map>

// using namespace std;


/*
# 題目:
    Given: string "s" (len = n)
    Output: int (Longest Substring length Without Repeating Characters)
    !Note: must be a substring
        ex: Input: s = "pwwkew", "pwke" is a subsequence and not a substring.
# My thoughts:
    1. Without Repeating -> set、ASCII code
*/

/*
    1️⃣ Brute Force- T:O(n * m); S:O(m)
        (1)Data structure: set
        (2)Algorithm: for loop
        Where: 
            n: the length of the string
            m: the total number of unique characters in the string.
*/

// class Solution {
// public:
//     int lengthOfLongestSubstring(string s) {
//         unordered_set<char> charSet;
//         int res = 0;

//         for (int i = 0; i < s.size(); i++) {
//             charSet.clear();
//             for (int j = i; j < s.size(); j++) { // 每新回合, j從頭i開始累計
//                 if (charSet.find(s[j]) != charSet.end()) {break;}
//                 charSet.insert(s[j]);
//             }
//             res = max(res, (int)charSet.size()); //也可用計數 tmpCnt++
//         }
//         return res;
//     }
// };


/*
    2️⃣ Sliding Window: 
        # Complexity- T:O(n); SO(m)
            Where: 
            n: the length of the string
            m: the total number of unique characters in the string.
        # 核心:(1)移動: Pointers(2)Data Storage: Hash Set
*/

// class Solution {
// public:
//     int lengthOfLongestSubstring(string s) {
//         unordered_set<char> charSet;
//         int l = 0;
//         int res = 0;

//         for (int r = 0; r < s.size(); r++) {
//             while (charSet.find(s[r]) != charSet.end()) { // duplicate
//                 charSet.erase(s[l]); // 從最左移除, while直到移除真正重複字元s[r] -> 重置
//                 l++;
//             }
//             charSet.insert(s[r]);
//             res = max(res, (int)charSet.size()); // charSet.size() == r - l + 1
//         }
//         return res;
//     }
// };


/*
    3️⃣ Sliding Window (Optimal)- T:O(n); S:O(m)
        Where: 
            n: the length of the string
            m: the total number of unique characters in the string.
        # 核心: 
            (1)方法 2 用 unordered_set 紀錄目前視窗有哪些字元，
                遇到重複 -> "逐個"移除；
            (2)方法 3 用 Map，記住每個字元上次(最近)的index，讓左邊界直接跳過去。
            (3)兩者都是平均 O(n)，方法 3 的優化: 省去逐個移除的操作。
*/

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> lastIndexMap;
        int l = 0;
        int res = 0;

        for (int r = 0; r < s.size(); r++) {
            if (lastIndexMap.find(s[r]) != lastIndexMap.end()) { // 若s[r]曾有記錄 -> 判斷是否在當前window
                l = max(l, lastIndexMap[s[r]] + 1); // 也可寫: if (lastIndexMap[s[r]] >= l) {l = l + 1;} // 若 < l, 則l不動
            }
            lastIndexMap[s[r]] = r; // ⚠️不能用 .insert({, }) -> 否則同char對應多紀錄(就要判斷lastIndex)
            res = max(res, r - l + 1); // 這裡不能用lastIndexMap.size(), 因為不是法2的set有erase
        }
        return res;
    }
};


// int main() {
//     string s;
//     cout << "input string: "; cin >> s;

//     Solution sol;
//     int result = sol.lengthOfLongestSubstring(s);

//     cout << "Length of longest substring without repeating characters: " << result << endl;
//     return 0;
// };