// g++ -std=c++17 -Wall -Wextra -g3 /Users/xiang13air/Program/Leetcode/Test.cpp -o /Users/xiang13air/Program/Leetcode/output/Test

// # include <iostream>
// # include <vector>
// #include <sstream>
// #include <unordered_map>
// #include <algorithm>
// #include <limits>
// using namespace std;

// # Given: an array of strings strs
// # Goal: group all anagrams together into sublists
// # return: the output in any order

// # def: An anagram is a string that contains the exact same characters as another string, but the order of the characters can be different.
// # Constraints: strs[i] is made up of lowercase English letters.
// # aim for a solution: with O(m * n) time and O(m) space, where m is the number of strings and n is the length of the longest string.
// # ------------------------------------------------
// # Solution: (1)Sorting(key=sorted string, value:original strings) (2)Dicationary(26字母 + count)- {tuple(count): List[str]}

class Solution {
public:
// // sol1️⃣: sorting
//     vector<vector<string>> groupAnagrams(vector<string>& strs) {
//         unordered_map<string, vector<string>> res_map;
//         for (const auto& s : strs) {
//             string sortedS = s; // 排序前複製
//             sort(sortedS.begin(), sortedS.end()); //in-place 不回傳
//             res_map[sortedS].push_back(s);
//         }
//         vector<vector<string>> res;
//         for (const auto& eachPair : res_map) { 
//             res.push_back(eachPair.second); // 🔥不是.second()!!!
//         }
//         return res; // ⚠️不能直接回傳res.second!!!(整個 unordered_map，本身沒有 .second。.second 是 map 裡面「每一個元素 pair」才有的。)
//     }
// // sol 2️⃣: Dicationary(26字母 + count)- {tuple(count): List[str]}
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> alpha_map;
        for (const auto& s : strs) {
            vector<int> alpha_count(26, 0);
            for (const auto& c : s) {
                alpha_count[c - 'a']++;
            }
            string key = to_string(alpha_count[0]);
            for (int i = 1; i < 26; i++) { // 第一個已經to_string了!
                key += ", " + to_string(alpha_count[i]);
            }
            alpha_map[key].push_back(s);
        }
        vector<vector<string>> res;
        for (const auto& item : alpha_map) {
            res.push_back(item.second);
        }
        return res;
    }
};

// // 檢查是否只包含小寫英文字母，允許空字串 ""
// bool isLowercaseEnglishString(const string& s) {
//     for (const char c : s) {
//         if (c < 'a' || c > 'z') {
//             return false;
//         }
//     }
//     return true;
// }

// vector<string> parseStringArray(const string& line) {
//     vector<string> strs;

//     size_t left = line.find('[');
//     size_t right = line.rfind(']');

//     if (left == string::npos || right == string::npos || left > right) {
//         throw invalid_argument("請輸入像 [\"eat\",\"tea\"] 的格式");
//     }

//     string content = line.substr(left + 1, right - left - 1);

//     for (size_t i = 0; i < content.size(); ) {
//         while (i < content.size() && (content[i] == ' ' || content[i] == ',')) {
//             i++;
//         }

//         if (i >= content.size()) break;

//         if (content[i] != '"') {
//             throw invalid_argument("字串必須用雙引號包起來");
//         }

//         i++; // skip opening "

//         string word;
//         while (i < content.size() && content[i] != '"') {
//             word += content[i];
//             i++;
//         }

//         if (i >= content.size()) {
//             throw invalid_argument("缺少結尾雙引號");
//         }

//         i++; // skip closing "
//         strs.push_back(word);
//     }

//     return strs;
// }

// int main() {
//     Solution sol;
//     string line;
    
//     while (true) {
//         try {

//             cout << "請輸入多組小寫英文字串(用空格分開): " << endl;
//             getline(cin, line);
//             if (line.empty()) {
//                 cout << "輸入為空!重新輸入!";
//                 // cin.clear();
//                 // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ⚠️通常 cin >> x 這樣才要清楚，如果用getline已經吃掉整行了!
//                 continue;
//             }

//             vector<string> strs = parseStringArray(line);

//             for (const string& s : strs) {
//                 if (!isLowercaseEnglishString(s)) {
//                     throw invalid_argument("只能輸入小寫英文字母");
//                 }
//             }
            
//             vector<vector<string>> result = sol.groupAnagrams(strs);

//             cout << "[";
//             for (size_t i = 0; i < result.size(); i++) {
//                 cout << "[";
//                 for (size_t j = 0; j < result[i].size(); j++) {
//                     cout << "\"" << result[i][j] << "\"";
//                     if (j != result[i].size() - 1) cout << ", ";
//                 }
//                 cout << "]";
//                 if (i != result.size() - 1) cout << ", ";
//             }
//             cout << "]" << endl;
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