# Given: integer array "digits"
# Return: after +1
# aim for: S:O(n) ; T: O(n)
# note: 1.no leading zero 2.

# Solution: 1.iteration 2.Recursion

class Solution:
    # S1:
    def plusOne(self, digits: List[int]) -> List[int]:
        n = len(digits)
        for i in range(n-1, -1, -1): # from right to left
            if digits[i] < 9:
                digits[i] += 1
                return digits # return immediately
            digits[i] = 0
        return [1] + digits
    # # S2:
    # def plusOne(self, digits:List[int]) -> List[int]:
    #     if not digits:
    #         return [1]
    #     if digits[-1] < 9:
    #         digits[-1] += 1
    #         return digits
    #     return self.plusOne(digits[:-1]) + [0]