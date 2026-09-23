class Solution:
    def isPalindrome(self, s:str) -> bool:  #主程式
        l, r = 0, len(s) - 1    #創建2個pointers,放最左/右

        while l < r:
            while l < r and not self.isAlphaNum(s[l]):   #也可用python內建函式s[l].isalnum()
                l += 1                  #跳過非目標字元（不處理）
            while r > l and not self.isAlphaNum(s[r]):  #left找到後換right找
                r -= 1

            #左右都找到後，開始比對
            if s[l].lower() != s[r].lower():    #記得轉換大小寫一致
                return False    #一有不同即return F,不用再繼續做完
            l, r = l + 1, r - 1     #若要繼續比對,需l向右、r向左,直到 l >= r,跳出while迴圈！！！
        return True     #通過以上逐一比對,都無不同 == 都相同

    def isAlphaNum(self, c):    #自定義main function會用到的函式。
        return (ord("A") <= ord(c) <= ord("Z") or   #ASCII編碼連續，若落在區間代表為其中一員
                ord("a") <= ord(c) <= ord("z") or   #用or，只要符合任何1個或以上，即為T
                ord("0") <= ord(c) <= ord("9"))

# '''
# #步驟：只保留 a-z A-Z 0-9 → 全部轉小寫 → 判斷是否回文。
# # pseudo code:
# '''
# class Solution:
#     def isPalindrome(self, s:str) -> bool:
        
#         res = []
#         for ch in s:
#             if ("A"<= ch <= "Z") or ("a" <= ch <= "z") or ("0" <= ch <= "9"):
#                 res.append(ch.lower())
            
#         return res == res[::-1]
    
# sol = Solution()
# print(sol.isPalindrome(input("請輸入字串:")))

# # 時間複雜度：O(n)，其中 n 是字串 s 的長度。需要遍歷整個字串一次來過濾和轉換字符，然後再比較兩個列表。
# # 空間複雜度：O(n)，在最壞情況下（當字串中所有字符都是英文字母或數字時），需要額外的空間來存儲過濾後的字符列表 res。