# Given: two strings s and t
# return: true if the two strings are anagrams of each other(, otherwise return false.)
# Definition: An anagram is a "string" that contains the "exact same characters" as another string, but the "order" of the characters can be different.
# T/S: aim for O(n + m) time and O(1) space
# Constraints: s and t consist of lowercase English letters.
# Solution: (1)Sorting (2)Hash Map

class Solution:
    ## (1)Sorting
    # def isAnagram(self, s:str, t:str) -> bool:
    #     if len(s) != len(t):
    #         return False    #若長度不同，則不用花費排序的時間

    #     return sorted(s) == sorted(t)
    ## (2)Hash Map
    def isAnagram(self, s:str, t:str) -> bool:
        if len(s) != len(t):
            return False
        countS, countT = {}, {}
        for i in range(len(s)):
            countS[s[i]] = 1 + countS.get(s[i], 0)
            countT[t[i]] = 1 + countT.get(t[i], 0)
        return countS == countT

# def main():
#     sol = Solution()
#     while True:
#         try:
#             s, t = input("請輸入兩組英文字串(用空格間隔): ").split()
#             if not s.isalpha() or not t.isalpha():
#                 print("請輸入有效的~英文~字串。")
#             else:
#                 print(sol.isAnagram(s, t))
#         except KeyboardInterrupt:
#             print("\nExiting the program.")
#             break
#         except ValueError as e:
#             print(f"An error occurred: {e}.\n(🔥請照規則輸入!!!)")
#             continue
#         except Exception as e:
#             print(f"An error occurred: {e}.\n(🔥請照規則輸入!!!)")
#             continue

# if __name__ == '__main__':
#     main()