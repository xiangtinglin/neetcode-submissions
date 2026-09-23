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
1.Bit Mask - I (Shift left對照)
2. Bit Mask - II (Shift right)
3. Bit Mask (Optimal🔥)-省時間:
Algorithm
Initialize a counter res = 0.
While n is not zero:
Update n = n & (n - 1) to remove the rightmost 1 bit
Increment res by 1
When n becomes 0, all 1 bits have been removed.
Return res.
'''
class Solution:
    def hammingWeight(self, n:int) -> int:
        res = 0
        while n:
            n &= (n - 1)
            res += 1
        return res
        