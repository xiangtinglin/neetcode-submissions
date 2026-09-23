# Design an algorithm: encode a list of strings to a string.
# 是 encode / decode，不是 encrypt / decrypt
# Thoughts: (1)找簡單有效規則處理字串 (2)Delimiter Design!!! (3)優化複雜度
# Sol: 常見—[length]#[content] (pitfall: 不能用 split("#"))
# Edge case: 注意input = [] or [""]區別
# 🔥note: Sol 1️⃣最好要保留 if not s，因為它後面直接用了：while s[i] != '#': ， 這行會直接存取 s[0]。如果 s = ""，就會爆掉。

class Solution:
    # def encode(self, strs: List[str]) -> str:
    #     # Sol1️⃣
    #     # EX: ["neet", "code", "you"] -> "4,4,3,#neetcodeyou"
    #     if not strs:
    #         return ""   # ""存在字串，但是空字串 = False
        
    #     sizes, res = [], ""
    #     for s in strs:
    #         sizes.append(len(s))
    #     for sz in sizes:
    #         res += str(sz)
    #         res += ","
    #     res += "#"
    #     for s in strs:
    #         res += s
    #     return res

    # def decode(self, s: str) -> List[str]:
    #     if not s:
    #         return []
    #     sizes, res, i = [], [], 0 # 還原
    #     while s[i] != "#":
    #         cur = ""
    #         while s[i] != ",":
    #             cur += s[i]
    #             i += 1
    #         sizes.append(int(cur))
    #         i += 1
    #     i += 1 # "#"下一位開始讀
    #     for sz in sizes:
    #         res.append(s[i:i + sz])
    #         i += sz
    #     return res
    
    def encode(self, strs: List[str]) -> str:
        # Sol2️⃣- Optimal
        # EX: ["neet", "code", "you"] -> "4#neet4#code3#you"
        res = ""
        for s in strs:
            res += str(len(s)) + "#" + s
        return res
    def decode(self, s: str) -> List[str]:
        res, i = [], 0
        while i < len(s):
            j = i
            while s[j] != "#":
                j += 1
            length = int(s[i:j])
            i = j + 1
            j = i + length
            res.append(s[i:j])
            i = j
        return res