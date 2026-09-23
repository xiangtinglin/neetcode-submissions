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
        while (i < s.size()) {
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