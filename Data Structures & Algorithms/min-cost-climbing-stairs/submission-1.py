class Solution:
    def minCostClimbingStairs(self, cost: List[int]) -> int:
        n = len(cost)
        df = [0] * (n + 1)

        for i in range(2, n+1):
            df[i] = min(df[i-1] + cost[i-1], df[i-2] + cost[i-2])
            
        return df[n]
        