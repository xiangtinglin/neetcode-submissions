/*
    # Given: the "sorted" rotated array nums of "unique" elements
    # return: the "minimum" element
    #  must : runs in O(log n) time.
*/

/*
1.Brute Force !!!不符合T複雜度!!!- T:O(n); S:O(1)
*/

// class Solution {
// public:
//     int findMin(vector<int>& nums) {
//         return *min_element(nums.begin(), nums.end());
//     }
// };

/*
2.Binary Search(Lower Bound)- T:O(log n); S:O(1)
    不用res = min(res, nums[l]) 逐次比較、存取
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;

        while (l < r) {    
            /*
            // 跟r比較-> 可辨別方向&無須先確認是否0 rotate -> (可選非必要寫 提前if判斷)
            // 跟l比較-> nums[m] > nums[l] 最小值方向不確定 -> 必先寫if判斷是否0 rotate
            
            if (nums[l] < nums[r]) {
                return nums[l]; // 直接回傳l為最小
            }
            */
            
            int m = l + ((r - l) / 2);
            if (nums[m] > nums[r]) { 
                l = m + 1;
            } else {
                r = m;
            }
        }
        return nums[l];
    }
};