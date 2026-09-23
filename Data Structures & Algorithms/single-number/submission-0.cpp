// '''
// given:a non-empty array of integers nums
// Return:the integer that appears only once.
// must implement:(1)runtime:O(n) (2)space:O(1)
// # 重點:
// 1. 空間限制:不能另外開空間
// 2. 時間:線性
// # 方法:
// 🔥🔥用XOR!!!XOR 的 3 個性質:
// (1)a ^ a = 0 
// (2)a ^ 0 = a 
// (3)交換律 + 結合律（超關鍵🔥不需要先排序，順序不重要）
// # ⚠️注意:
// 情境不同解法不同!例:只有一個single number或有多個single number!!!
// # 步驟:
// 1.處理Edge case
// 2.做XOR
// '''
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        if (nums.empty() ) {
            return 0;
        } 
        else {
            for (int num : nums) {
                res = res ^num;
            }
            return res;
        }
    }
};