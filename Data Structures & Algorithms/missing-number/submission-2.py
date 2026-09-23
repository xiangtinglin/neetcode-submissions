# Given: nums
# Return: single num(int)
# T / S: aim for - O(1) extra space complexity and O(n) runtime
# 方法: (1)Sorting (2)Hash Set (3)Bitwise XOR
class Solution:
    # def missingNumber(self, nums: List[int]) -> int:
    #     n = len(nums)
    #     nums.sort()     # T: O(n log n)
    #     for i in range(n):
    #         if nums[i] != i:
    #             return i
    #     return n    # 如果single num是最後一個,記得回傳!!!
    #     # S: O(1) or O(n) depending on the sorting algorithm.

    def missingNumber(self, nums: List[int]) -> int:
        nums_set = set(nums)    # S: (n)
        n = len(nums)           # S: (1)
        for i in range(n + 1):  # T: O(n)
            if i not in nums_set:
                return i
    # def missingNums(self, nums: List[int]) -> int:
