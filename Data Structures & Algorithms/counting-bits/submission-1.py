# # # # # class Solution:
# # # # #     def countBits(self, n: int) -> List[int]:
# # # # #         res = []
# # # # #         for num in range(n + 1):
# # # # #             count = 0
# # # # #             for i in range(32):
# # # # #                 if num & (1 << i):
# # # # #                     count += 1
# # # # #             res.append(count)
# # # # #         return res

# # # # class Solution:
# # # #     def countBits(self, n: int) -> List[int]:
# # # #         res = []
# # # #         for num in range(n + 1):
# # # #             count = 0
# # # #             while num:
# # # #                 num &= (num -1)
# # # #                 count += 1
# # # #             res.append(count)
# # # #         return res


# # # class Solution:
# # #     def countBits(self, n:int) -> List[int]:
# # #         res = [0] * (n + 1)
# # #         for i in range(1, n + 1):
# # #             num = i
# # #             while num != 0:
# # #                 num &= (num - 1)
# # #                 res[i] += 1
# # #         return res

# # class Solution:
# #     def countBits(self, n:int) -> List[int]:
# #         res = [0] * (n + 1)
# #         for i in range(n + 1):
# #             res[i] = bin(i).count('1')
# #         return res

# class Solution:
#     def countBits(self, n:int) -> List[int]:
#         dp = [0] * (n + 1)
#         offset = 1
#         for i in range(1, n + 1):
#             if offset * 2 == i:
#                 offset = i
#             dp[i] = 1 + dp[i - offset]
#         return dp

class Solution:
    def countBits(self, n:int) -> List[int]:
        dp = [0] * (n + 1)
        for i in range(1, n + 1):
            dp[i] = dp[i >> 1] + (i & 1)
        return dp