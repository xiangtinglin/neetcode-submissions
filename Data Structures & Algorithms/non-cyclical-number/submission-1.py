# Given: a positive integer "n"（replace it with the sum of the squares of its digits.）
# return: boolean （until the number equals 1, or it loops infinitely in a cycle）

# T / S: aim for O(logn) time and O(logn) space
# Solution: (1)Hash Set (2)Fast And Slow Pointers(Floyd's cycle detection)

class Solution:
    # def isHappy(self, n:int) -> bool:
    #     seen = set()
    #     while n not in seen:  # T: O(1)
    #         if n == 1:
    #             return True
    #         seen.add(n)
    #         n = self.sumOfSquares(n) # T: O(logn)
    #     return False

    def isHappy(self, n:int) -> bool:
        slow, fast = n, self.sumOfSquares(n) # 創建雙pointers # S: O(1)
        while slow != fast:
            if slow == 1:
                return True
            slow = self.sumOfSquares(slow)                      # slow一次走1回合
            fast = self.sumOfSquares( self.sumOfSquares(fast) ) # fast一次走2回合
        return slow == 1 # ❗️若n = 1, fast/slow不會進入while迴圈

    def sumOfSquares(self, n:int) -> int:
        temp = n
        res = 0

        while temp >= 1:
            digit = temp % 10   # 個位數數字
            digit *= digit
            res += digit
            temp = temp // 10   # 每輪解決一個個位數字
        return res
