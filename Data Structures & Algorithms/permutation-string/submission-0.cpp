/*
Ctrl + Shift + B：只編譯

clang++ -std=c++17 Test.cpp -o Test.exe
.\Test.exe

*/

// #include <iostream>
// #include <vector>
// #include <string>

// using namespace std;


/*
    # Given: strings "s1"、"s2"
    # Return: true / false
    # Core: 
        1.permutation -> sort
        2.substring(contain) 
        3.最重要的轉換：「排列問題」轉成「字元次數比較」 -> HashMap
    # Thoughts: 
        1. 注意:
            (1) 邏輯盲點（僅用 Set 無法正確判斷排列）:permutation（排列），字元不僅要存在，出現的次數（頻率）也要完全一致。使用 unordered_set 只檢查「有沒有出現」，無法處理重複字元!!!
    
    # Ask: (1)lower / upper case?
*/

/*
    一、Brute Force- T:O(n * m log m); S:O(m)
        Where m is the length of the s1 and n is the length of s2.
        # 核心: (1)雙 loop (2)Sort then Compare!!!
*/


// class Solution {
// public:
//     bool checkInclusion(string s1, string s2) {
//         int s1L = s1.size(), s2L = s2.size();
//         sort(s1.begin(), s1.end());

//         for (int i = 0; i < s2L; i++) { // !!!不要寫: i < s2L - s1L + 1 -> s1 長度可能 > s2
//             // for (int j = i; j < s2L; j++) {
//                 string subStr = s2.substr(i, s1L); // 注意.subStr(int startIndex, int len)
//                 sort(subStr.begin(), subStr.end());
//                 if (subStr == s1) {return true;}
//             // }
//         }
//         return false;
//     }
// };


/*
    二、HashMap- T:O(n * m); S:O(26) ≈ O(1) 
        # Core: 用Map比對 -> 不用Sort(省時)
*/

// class Solution {
// public:
//     bool checkInclusion(string s1, string s2) {
//         // 先計算對照字元數
//         unordered_map<char, int> count1;
//         for (char c : s1) {count1[c]++;}

//         int need = count1.size(); // 需要字元對應頻率全符合

//         unordered_map<char, int> count2;
//         for (int i = 0; i < s2.size(); i++) {
//             count2.clear();
//             int needCnt = 0;
//             for (int j = i; j < s2.size(); j++) {
//                 char c = s2[j];
//                 count2[c]++;
//                 // 判斷條件, < 或 == 都沒事!
//                 if (count1[c] < count2[c]) {break;} // 如 count1 沒 c，count1[c] 會自動新增這個 key，並初始化成 0 -> 條件成立，執行 break。
//                 if (count1[c] == count2[c]) {needCnt++;} //累積
                
//                 if (needCnt == need) {return true;}
//             }
//         }
//         return false;
//     }
// };


/*
    三、Sliding Window- T:O(n); S:O(26) ≈ O(1)
        # 核心: (1)pointer- l, r (2)vector<int> alphabetFrequency(26, 0); (3)更新vector & 計算window變化狀態頻率match

*/

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int s1L = s1.size(), s2L = s2.size();

        if (s1L > s2L) {return false;} // 此法要先排除長度問題 -> 因後面用vector 26字母頻率, 初始化若s2[i]超出範圍會error!!!

        // initial, 先記錄s1的alphabet頻率(對應s2的前i個)
        vector<int> s1V(26, 0);
        vector<int> s2V(26, 0);
        for (int i = 0; i < s1L; i++) { // 更新前i個對應頻率, 後面其他沒更新的已初始化為0 -> s1V之後都固定不變!!!
            s1V[s1[i] - 'a']++; // !!!注意: char 用''; string 用""!!!
            s2V[s2[i] - 'a']++;
        }

        int match = 0; // 看總共?個match: 除了當前window(各自前i個)對應頻率, 其他都同初始化0 -> 所以當前window更新後Vector狀態要26才符合
        for (int i = 0; i < 26; i++) {
            if (s1V[i] == s2V[i]) {match++;} // 26 - match = 不一致的部分(需要靠window更新後對齊)
        }

        int l = 0;
        for (int r = s1L; r < s2L; r++) { // 記得從 r = s1L 開始, 前面已算前i個, 整個過程s1V都固定不變!!!
            if (s1V == s2V) {return true;} // 更新前先檢查是否剛好前window已符合(放後面 -> 可能會錯過一開始window組!!!), 也可寫 s1V == s2V

            // (1)處理新字母(rightmost)
            int index = s2[r] - 'a';
            s2V[index]++;
            if (s1V[index] == s2V[index]) {match++;}
            else if (s1V[index] == s2V[index] - 1) {match--;} // 若原本加之前相等 ->加完後必不同, 要減去!!!

            // (2)處理要移除的(leftmost)
            index = s2[l] - 'a';  // !!!注意: 前面已宣告int index -> 不得再次宣告(覆蓋賦新值即可) ->int要去除!!!
            s2V[index]--;
            if (s1V[index] == s2V[index]) {match++;}
            else if (s1V[index] == s2V[index] + 1) {match--;}

            l++;
        }
        return s1V == s2V;
    }
};


// int main() {
//     Solution sol;
//     string s1, s2;

//     cout << "Check if s2 contains a permutation of s1: \n";
//     cout << "Test Case 1: " <<endl;
//     cout << "  Input string 1: "; cin >> s1; 
//     cout << "  Input string 2: "; cin >> s2;

//     bool result = sol.checkInclusion(s1, s2);
//     cout << "  Result: " << (result ? "true" : "false") << endl;

//     return 0;
// }