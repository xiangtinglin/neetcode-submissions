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