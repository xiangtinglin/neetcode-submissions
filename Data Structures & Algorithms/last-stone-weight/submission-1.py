'''note'''
# an array of integers stones,stones[i] is the weight
# choose the heaviest two stones and smash -> 0 /  y - x
# at most one stone left（0/1）
# Return the weight of the last remaining stone

class Solution:
    def lastStoneWeight(self, stone:List[int]) -> int:
        while len(stone) > 1:      # 先處理
            stone.sort(reverse=False) # ⚠️.sort()跟sorted()
            smashed = stone.pop() - stone.pop() # 預設:移除並回傳最後一個元素（index = -1）
            if smashed:    # 或寫 if smashed !=0:
                stone.append(smashed)
        return stone[0] if stone else 0

