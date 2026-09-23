# Given: nums
# Return: single num(int)
# T / S: aim for - O(1) extra space complexity and O(n) runtime
# 方法: (1)Sorting (2)Hash Set (3)Bitwise XOR (4)Math(加減)
class Solution:
    # def missingNumber(self, nums: List[int]) -> int:
    #     n = len(nums)
    #     nums.sort()     # T: O(n log n)
    #     for i in range(n):
    #         if nums[i] != i:
    #             return i
    #     return n    # 如果single num是最後一個,記得回傳!!!
    #     # S: O(1) or O(n) depending on the sorting algorithm.

    # def missingNumber(self, nums: List[int]) -> int:
    #     nums_set = set(nums)    # S: (n)
    #     n = len(nums)           # S: (1)
    #     for i in range(n + 1):  # T: O(n)
    #         if i not in nums_set:
    #             return i

    # def missingNumber(self, nums: List[int]) -> int:
    #     n = len(nums)
    #     xor_res = n     # nums的最大數字
    #     for i in range(n):
    #         xor_res ^= i ^ nums[i]  # 使用了xor特性: (1)a^a = 0; a^0 = a (2)交換、結合率
    #     return xor_res
    #     # T: O(n); S: O(1)

    def missingNumber(self, nums: List[int]) -> int:
        n = len(nums)
        math_res = n
        for i in range(n):
            math_res += i - nums[i] # 全部加減後的數字就是缺的single number(最大的數n只會在一開始加一次)
        return math_res
        # T: O(n); S: O(1)