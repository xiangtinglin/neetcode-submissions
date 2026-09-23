class Solution {
// S1: Iteration

public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size();
        for (int i = n - 1; i >= 0; i--) {
            if (digits[i] < 9) {
                digits[i] += 1;
                return digits;
            }
            digits[i] = 0;
        }
        vector<int> res(n + 1, 0);
        res[0] = 1;
        return res; // 不能直接寫: return [1] + digits
    }


// // S2: Recursion
// public:
//     vector<int> plusOne(vector<int>& digits) {
//         if (digits.empty()) {
//             return {1}; // ‼️原本不能直接寫{}({}非資料結構用途),是initial_list, 但是因為函式早已定義回傳的type, 所以可以自動推!
//         }
//         if (digits.back() < 9) {
//             digits.back() += 1;
//             return digits;
//         }
//         digits.pop_back();
//         vector<int> res = plusOne(digits);
//         res.push_back(0);
//         return res;
//     }
// };

// int main() {
//     Solution sol;

//     string s;
//     cin >> s;

//     vector<int> digits;
//     for (char c : s) {
//         if (isdigit(c)) { // ‼️沒if (isdigit(c)) 就不能處理[1, 2, 3], 只能處理這種 123
//             digits.push_back(c - '0');
//         }
//         // C++ 中，字元用 ASCII code（數字） 存的（’0’ 的ASCII code是48；‘1’是49）
//         // ❌千萬不能寫: digits.push_back(c); 會變成 ASCII，例如 '5' -> 53
//     }
//     vector<int> ans = sol.plusOne(digits);
//     cout << "[";
//     for (int i = 0; i < ans.size(); i++) {
//         cout << ans[i];
//         if (i != ans.size()-1) {
//             cout << ", ";
//         }
//     }
//     cout << "]";
};