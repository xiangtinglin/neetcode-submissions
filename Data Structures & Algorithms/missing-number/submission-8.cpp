class Solution {
public:
    // int missingNumber(vector<int>& nums) {
    //     int n = nums.size();
    //     sort(nums.begin(), nums.end());
    //     for (int i = 0; i < n; i++) {
    //         if (i != nums[i]) {
    //             return i;
    //         }
    //     }
    //     return n;
    // }

    // int missingNumber(vector<int>& nums) {
    //     int n = nums.size();
    //     unordered_set<int> set_nums(nums.begin(), nums.end());
    //     for (int i = 0; i <= n; i++) {
    //         if (set_nums.find(i) == set_nums.end()) {
    //             return i;
    //         }
    //     }
    //     return -999;    // 防呆設計
    // }

    // int missingNumber(vector<int>& nums) {
    //     int n = nums.size();
    //     int xorr = n;
    //     for (int i = 0; i < n; i++) {
    //         xorr ^= i ^ nums[i];
    //     }
    //     return xorr;
    // }

    int missingNumber(const vector<int>& nums) {
        int n = nums.size();
        int math_method = n;
        for (int i = 0; i < n; i++) {
            math_method += i - nums[i];
        }
        return math_method;
    }
};