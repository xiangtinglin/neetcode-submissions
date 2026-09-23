'''
# given:an unsigned integer n
# Return: the number of 1 bits (in its binary representation.)
# assume: n is a non-negative integer which fits within 32-bits.
————
# Complexity:
aim for a solution with O(1) time and O(1) space.
# 核心特性:
(1)位元運算!(32-bits) 
(2)善用運算性質「&」
# 解法
1.Bit Mask - I
'''
class Solution:
    def hammingWeight(self, n:int) -> int:
        res = 0
        for i in range(32):
            if (1 << i) & n:
                res += 1
        return res
        