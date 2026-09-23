class Solution:
    def isPalindrome(self, s: str) -> bool:
        l, r = 0, len(s) - 1

        while l < r:
            while l < r and not s[l].isalnum():  # 使用內建的 isalnum() 來檢查字母數字
                l += 1
            while r > l and not s[r].isalnum():  # 同上
                r -= 1
            if s[l].lower() != s[r].lower():  # 無需自定義 alphaNum 函數
                return False
            l, r = l + 1, r - 1
        return True
