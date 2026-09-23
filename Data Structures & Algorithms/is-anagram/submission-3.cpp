// g++ -std=c++17 -Wall -Wextra -g3 Test.cpp -o output/Test_cpp

// # include <iostream>
// # include <vector>
// #include <sstream>
// #include <unordered_map>
// #include <algorithm>
// #include <limits>
// using namespace std;


// # Given: two strings s and t
// # return: true if the two strings are anagrams of each other(, otherwise return false.)
// # Definition: An anagram is a "string" that contains the "exact same characters" as another string, but the "order" of the characters can be different.
// # T/S: aim for O(n + m) time and O(1) space
// # Constraints: s and t consist of lowercase English letters.
// # Solution: (1)Sorting (2)Hash Map

class Solution {
// // (1)Sorting
// public:
//     bool isAnagram(string s, string t) {
//         if (s.size() != t.size()) {
//             return false;
//         }
//         sort(s.begin(), s.end());
//         sort(t.begin(), t.end());
//         return s == t;
//         // ⚠️不能寫 return sort(s.begin(), s.end()) == sort(t.begin(), t.end()); 👉（sort()：的回傳型別是 void，沒有回傳值）
//     }
// (2)Hash Map
public:
    bool isAnagram(string s, string t) {
        if (s.size() != t.size()) {
            return false;
        }
        unordered_map<char, int> countS; // ⚠️是char，不是string
        unordered_map<char, int> countT;
        for (int i = 0; i < s.size(); i++) {
            countS[s[i]] ++; // # ⚠️Python不能直接+= 1，但C++可以（C++ 重要的特性：如果key不存在，會自動建立它。而且：對 int 來說，會自動初始化成：0）
            countT[t[i]] ++;
        }
        return countS == countT;
    }
};

// bool isAlphaString(const string& str) {
//     for (char c : str) {
//         if (!isalpha(c)) {
//             return false;
//         }
//     }
//     return true;
// }

// int main() {
//     Solution sol;
//     string line;
    
//     while (true) {
//         try {
//             cout << "請輸入'兩組英文'字串(用空格分開): " << endl;
//             getline(cin, line);
//             if (line.empty()) {
//                 cout << "輸入為空!重新輸入!";
//                 // cin.clear();
//                 // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ⚠️通常 cin >> x 這樣才要清楚，如果用getline已經吃掉整行了!
//                 continue;
//             }
//             stringstream ss(line);
//             string s, t, extra;
//             if (!(ss >> s >> t) || (ss >> extra)) { // ⚠️若少於2個 or 能取出多於2個字串為錯!
//                 cout << "請輸入'剛好兩組'英文字串(用空格分開)!" << endl;
//                 continue;
//             }
//             if (!isAlphaString(s) || !isAlphaString(t)) {
//                 cout << "請輸入兩組'英文'字串(用空格分開)!" << endl;
//                 continue;
//             } else {
//                 cout << boolalpha << sol.isAnagram(s, t) << endl;
//             }
//         }
//         catch (const invalid_argument& e) {
//             cout << "An error occurred: " << e.what()
//                 << "\n(🔥請照規則輸入!!!)" << endl;
//             continue;
//         }
//         catch (const exception& e) {
//             cout << "Unexpected error: " << e.what()
//                 << "\n(🔥請照規則輸入!!!)" << endl;
//             continue;
//         }
//     }
//     return 0;
// };