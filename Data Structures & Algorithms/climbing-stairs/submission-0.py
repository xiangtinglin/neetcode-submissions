'''
# 變數: (1)n:steps (2)climb:1 or 2
# Constraints:1 <= n <= 45
# target:(1)time:O(n) (2)space:O(n)
'''
class Solution:
    def climbStairs(self, n:int) -> int:
        one, two = 1, 1      # 創建2個pointers賦值
        for i in range(n-1): # 迴圈數 = 計算次數(n-1)
            temp = one       # 用一個暫存容器儲存one(因為等等加法後會覆蓋)
            one = one + two
            two = temp
        return one