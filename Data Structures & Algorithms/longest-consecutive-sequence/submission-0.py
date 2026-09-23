# from typing import List
# import ast
# Clarify: 重複數字不影響連續長度 -> 重複不計 -> set()

class Solution:
    # def longestConsecutive(self, nums: List[int]) -> int:
    #     # 1️⃣ Hash Set -> T/S: O(n)
    #     nums_set = set(nums)
    #     res = 0

    #     for num in nums_set: # 可不用先排序
    #         streak, curr = 0, num
    #         if (curr - 1) not in nums_set: # 🔥避免重複計算(只從第一個開始), 沒這個的話就是Brute Force
    #             while curr in nums_set:
    #                 streak += 1
    #                 curr += 1
    #             res = max(res, streak)
    #     return res

    # 2️⃣ Sorting -> T: O(nlogn) S: O(1) or O(n) depending on the sorting algorithm.
    def longestConsecutive(self, nums: List[int]) -> int:
        if not nums:
            return 0
        nums.sort()
        
        res = 0
        streak, curr = 0, nums[0]
        i = 0
        while i < len(nums):
            if curr != nums[i]:
                curr = nums[i]
                streak = 0
            while i < len(nums) and nums[i] == curr:
                i += 1
            streak += 1
            curr += 1
            res = max(res, streak)
        return res
    
# def main():
#     sol = Solution()
#     while True:
#         try:
#             user_input = input("請輸入整數陣列：")

#             if user_input.startswith("["):
#                 strs = ast.literal_eval(user_input)
#             else:
#                 strs = list(map(int, user_input.split()))

#             anwer = sol.longestConsecutive(strs)
#             print("Answer: ", anwer)

#         except KeyboardInterrupt:
#             print("\nExiting the program.")
#             break
#         except ValueError as e:
#             print(f"An error occurred: {e}.\n(🔥請照規則輸入!!!)")
#             continue
#         except Exception as e:
#             print(f"An error occurred: {e}.\n(🔥請照規則輸入!!!)")
#             continue

# if __name__ == '__main__':
#     main()