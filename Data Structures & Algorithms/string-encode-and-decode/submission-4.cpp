// g++ -std=c++17 -Wall -Wextra -g3 /Users/xiang13air/Program/Leetcode/Test.cpp -o /Users/xiang13air/Program/Leetcode/output/Test

// # Given: an integer array nums and an integer k
// # return: the k most frequent elements within the array.
// # thoughts: hash map + count {key = num : value = count}
// # Complexity: aim for O(n) time and O(n) space (where n is the size of the input array).
// '''
// EX: nums = [1, 1, 1, 2, 2, 3] , k = 2
// Sol 1: 極致Pythonic!!!（Tools）
// Sol 2: 實作Sorting
// Sol 3: Min-Heap(前k大)— 🔥C++預設是max-heap!!!
// Sol 4: Bucket Sort
// '''

# include <iostream>
# include <vector>
# include <unordered_map>
# include <queue>
# include <algorithm>
# include <string>

using namespace std;
// # Design an algorithm: encode a list of strings to a string.
// # 是 encode / decode，不是 encrypt / decrypt
// # Thoughts: (1)找簡單有效規則處理字串 (2)Delimiter Design!!! (3)優化複雜度
// # Sol: 常見—[length]#[content] (pitfall: 不能用 split("#"))
// # Edge case: 注意input = [] or [""]區別
// # 🔥note: Sol 1️⃣最好要保留 if not s，因為它後面直接用了：while s[i] != '#': ， 這行會直接存取 s[0]。如果 s = ""，就會爆掉。

class Solution {
public:
    // // # Sol1️⃣
    // // # EX: ["neet", "code", "you"] -> "4,4,3,#neetcodeyou"
    // string encode(const vector<string>& strs) {
    //     if (strs.empty()) {
    //         return "";
    //     }
    //     vector<int> sizes;
    //     string res = "";
    //     for (const string& s : strs) {
    //         sizes.push_back(s.size());
    //     }
    //     for (int sz : sizes) {
    //         res += to_string(sz) + ',';
    //     }
    //     res += '#';
    //     for (const string& s : strs) {
    //         res += s;
    //     }
    //     return res;
    // }
    // // # EX: "4,4,3,#neetcodeyou" -> ["neet", "code", "you"] 
    // vector<string> decode(const string& s) {
    //     if (s.empty()) {
    //         return {};
    //     }
    //     vector<int> sizes;
    //     vector<string> res;
    //     int i = 0;
    //     while (s[i] != '#') {
    //         string cur = "";
    //         while (s[i] != ',') {
    //             cur += s[i];
    //             i++;
    //         }
    //         sizes.push_back(stoi(cur));
    //         i++;
    //     }
    //     i++;
    //     for (int sz : sizes) {
    //         res.push_back(s.substr(i, sz));  // C++要用: s.substr(start, length)
    //         i += sz;
    //     }
    //     return res;
    // }

    // // # Sol 2️⃣
    // // # EX: ["neet", "code", "you"] -> "4#neet4#code3#you"
    string encode(const vector<string>& strs) {
        string res = "";
        for (const string& s : strs) {
            res += to_string(s.size()) + '#' + s;
        }
        return res;
    }
    // // # EX:  "4#neet4#code3#you" -> ["neet", "code", "you"]
    vector<string> decode(const string& s) {
        vector<string> res;
        int i = 0;
        while (i < static_cast<int>(s.size())) {
            int j = i;
            while (s[j] != '#') {
                j++;
            }
            int length = stoi(s.substr(i, j - i));
            i = j + 1;
            j = i + length;
            res.push_back(s.substr(i, length));
            i = j;
        }
        return res;
    }
};

// int main()
// {
//     vector<string> nums = {"neet", "code", "you"};

//     Solution sol;
//     string encoded = sol.encode(nums);
//     cout << "encoded: " << encoded << endl;
//     vector<string> decoded = sol.decode(encoded);
//     cout << "decoded: ";

//     cout << "[";
//     for (const string& str : decoded) {
//         cout << '"' << str << '"';
//         if (str != decoded.back()) {
//             cout << ", ";
//         }
//     }
//     cout << "]" << endl;


//     return 0;
// }
