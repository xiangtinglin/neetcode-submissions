# from typing import List

class Solution:
    def countBits(self, n:int) -> List[int]:
        dp = [0] * (n + 1)
        for i in range(1, n + 1):
            dp[i] = dp[i >> 1] + (i & 1)
        return dp

# def main():
#     while True:
#         sol = Solution()
#         try:
#             n = int(input("Enter a integer: "))
#             print(sol.countBits(n))

#         except KeyboardInterrupt:
#             print("\nExiting the program.")
#             break
#         except Exception as e:
#             print(f"An error occurred: {e}")
#             continue

# if __name__ == "__main__":
#     main()