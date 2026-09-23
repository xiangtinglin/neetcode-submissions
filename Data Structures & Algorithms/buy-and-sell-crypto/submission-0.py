class Solution:
    def maxProfit(self, prices:List[int]) -> int:
        l, r = 0, 1     # left:買價、right：賣價（先買才能賣，l < r）
        maxP = 0        # initialize 預設0

        while r < len(prices):          # r需遍歷到最後一個price
            if prices[l] < prices[r]:   # 漲時：有利潤，計算利潤值
                profit = prices[r] - prices[l]
                maxP = max(maxP, profit)   # 當前與歷史最大利潤比較
            else:       # 跌/持平：設定低價為買價
                l = r
            r += 1      # 繼續看隔天價格，直到結束
        return maxP     # 回傳最大利潤值

