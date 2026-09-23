# Given: 32-bit unsigned integer n
# Goal: reverse the bits of the binary representation of n
# T / S: aim for O(1) time and O(1) space.

class Solution:
    def reverseBits(self, n: int) -> int:
        res = n
        res = (res & 0xFFFF0000) >> 16 | (res & 0x0000FFFF) << 16
        res = (res & 0xFF00FF00) >> 8 | (res & 0x00FF00FF) << 8
        res = (res & 0xF0F0F0F0) >> 4 | (res & 0x0F0F0F0F) << 4
        res = (res & 0xCCCCCCCC) >> 2 | (res & 0x33333333) << 2
        res = (res & 0xAAAAAAAA) >> 1 | (res & 0x55555555) << 1
        res = res & 0xFFFFFFFF
        return res