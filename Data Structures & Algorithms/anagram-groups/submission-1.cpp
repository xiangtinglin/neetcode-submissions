// # Given: an array of strings strs
// # Goal: group all anagrams together into sublists
// # return: the output in any order

// # def: An anagram is a string that contains the exact same characters as another string, but the order of the characters can be different.
// # Constraints: strs[i] is made up of lowercase English letters.
// # aim for a solution: with O(m * n) time and O(m) space, where m is the number of strings and n is the length of the longest string.
// # ------------------------------------------------
// # Solution: (1)Sorting(key=sorted string, value:original strings) (2)Dicationary(26字母 + count)- {tuple(count): List[str]}

class Solution {
    // sol1️⃣: sorting
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> res_map;
        for (const auto& s : strs) {
            string sortedS = s; // 排序前複製
            sort(sortedS.begin(), sortedS.end()); //in-place 不回傳
            res_map[sortedS].push_back(s);
        }
        vector<vector<string>> res;
        for (const auto& eachPair : res_map) {
            res.push_back(eachPair.second); // 🔥不是.second()!!!
        }
        return res;
    }
};