# Given: an array of strings strs
# Goal: group all anagrams together into sublists
# return: the output in any order

# def: An anagram is a string that contains the exact same characters as another string, but the order of the characters can be different.
# Constraints: strs[i] is made up of lowercase English letters.
# aim for a solution: with O(m * n) time and O(m) space, where m is the number of strings and n is the length of the longest string.
# ------------------------------------------------
# Solution: (1)Sorting(key=sorted string, value:original strings) (2)Dicationary(26字母 + count) 

# import ast
# from typing import List

class Solution:
#     # sol 1️⃣
#     def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
#         # 1. create a hash map
#         res_dict = {} 
#         # 2. iterate through each string
#         for s in strs:
#             # (1)Sorted string as a key
#             sorted_s = "".join(sorted(s))

#             if sorted_s not in res_dict:  # note: defaultdict(list)
#                 res_dict[sorted_s] = []
#             # (2)append the original string to the list (corresponding to the key)
#             res_dict[sorted_s].append(s)
#         # 3. return all values from the hash map
#         return list(res_dict.values())
    
    # sol 2️⃣
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        # 1. create a hash map- {tuple(count): List[str]}
        res_dict = defaultdict(list)
        # 2. iterate through each string
        for s in strs:
            # (1) Initialize a count array
            count = [0] * 26
            # (2) increment the count
            for c in s:
                count[ord(c) - ord("a")] += 1
            res_dict[tuple(count)].append(s)
        # 3. return all the lists stored in the hash map.
        return list(res_dict.values())
    
# def main():
#     sol = Solution()
#     while True:
#         try:
#             user_input = input("請輸入字串陣列：")

#             if user_input.startswith("["):
#                 strs = ast.literal_eval(user_input)
#             else:
#                 strs = user_input.split()

#             print(sol.groupAnagrams(strs))

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