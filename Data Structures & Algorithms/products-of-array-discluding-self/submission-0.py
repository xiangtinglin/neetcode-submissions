# 1. Datatype: Given an integer array(nums), return an array(answer)
# 2. Action: answer[i] is equal to the product of all the elements of nums except nums[i]
# 3. Complexity: 
# (1) must run in O(n) time.
# (2) Follow up: O(1) extra space?
# 4. Constraints:
# (1) 2 <= nums.length <= 105
# (2) -30 <= nums[i] <= 30
# (3) The input is generated such that answer[i] is guaranteed to fit in a 32-bit integer.
# note: 🔥without using the division operation -> 一旦分母有0，無法靠「總乘積」還原資訊。
# 5. Solution:
# (1) Brute Force: T = O(n*2)
# (2) Prefix & Suffix Product(非DP)
# EX: Input: nums = [-1,1,0,-3,3] / Output: [0,0,9,0,0]

# from typing import List
# import ast

class Solution:
    # def productExceptSelf(self, nums: List[int]) -> List[int]:
        # # (1) Brute Force: T = O(n*2)
        # n = len(nums)
        # res = []
        # for i in range(n):
        #     prod = 1
        #     for j in range(n):
        #         if i == j:
        #             continue
        #         prod *= nums[j]
        #     res.append(prod)
        # return res

    # # (2) Prefix & Suffix Product
    # def productExceptSelf(self, nums: List[int]) -> List[int]:
    #     n = len(nums)
    #     left = [0] * n
    #     right = [0] * n
    #     res = [0] * n

    #     left[0], right[n - 1] = 1, 1  # 最左、右的值先設1
    #     for i in range(1, n): # prefix，從1開始
    #         left[i] = nums[i - 1] * left[i - 1]
    #     for i in range(n-2, -1, -1): # suffix
    #         right[i] = nums[i + 1] * right[i + 1]
    #     for i in range(n): # res
    #         res[i] = left[i] * right[i]
    #     return res

    # (3) Prefix & Suffix Product(Optimal: Space)
    # EX: Input: nums = [-1,1,0,-3,3] / Output: [0,0,9,0,0]
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        n = len(nums)
        res = [1] * n # 會使用到乘積，所以初始化為1

        left = 1    # 不新開容器，只開一個整數空間，利用res
        for i in range(n): # 先填left(res先放left內容)
            res[i] = left
            left = res[i] * nums[i]

        right = 1 
        for i in range(n-1, -1, -1):
            res[i] *= right
            right *= nums[i]
            
        return res
    
# sol = Solution()
# while True:
#     try:
#         nums = list( map (int, (input("請輸入一串數字:").split() ) ) )
#         print(sol.productExceptSelf(nums))
#     except KeyboardInterrupt:
#         print("\n(程式結束!)")
#         break
#     except Exception as e:
#         print("原因:", e)
