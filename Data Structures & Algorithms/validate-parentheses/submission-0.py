class Solution:
    def isValid(self, s:str) -> bool:
        stack = []
        closeToOpen = { ")":"(", "]":"[", "}":"{" }

        for p in s:
            if p in closeToOpen:        #遇到close bracket(key值)時
                if stack and stack[-1] == closeToOpen[p]:
                    stack.pop()
                else:
                    return False
            else:
                stack.append(p)        #否則，把open bracket(value值)放進stack
        
        return True if not stack else False     #全部跑完之後，stack都被poped out配對完為True；反之為否。
            