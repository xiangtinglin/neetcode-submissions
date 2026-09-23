# Given: an array [nums] containing n integers in the range [0, n] (without any duplicates)
# return: the single number (in the range) that is missing from nums.
# T / S: aim for a solution with O(n) time and O(1) space

# Sol: (1)Sort -> 對照 (2)bitwise XOR
# ✅ 性質1：自己 XOR 自己 = 0
# a ^ a = 0
# ✅ 性質2：跟 0 XOR 不變
# a ^ 0 = a
# ✅ 性質3：交換律 + 結合律
# a ^ b ^ a = (a ^ a) ^ b = 0 ^ b = b

class Solution:
    def missingNumber(self, nums: List[int]) -> int:
        n = len(nums)
        nums.sort()
        for i in range(n):
            if i != nums[i]:
                return i
        return n    # 若缺乏的是最後一個最大的數!!!