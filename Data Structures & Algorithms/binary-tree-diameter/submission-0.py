# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

class Solution:
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        max_dia = 0     # 紀錄最長path,不能放dfs裡面，避免每次call自己被刷新歸0

        def dfs(node):
            nonlocal max_dia # 要調用外層變數

            if not node:
                return 0
            left = dfs(node.left)  # ⚠️不要self.dfs !!!因為不是在Solution層級的function
            right = dfs(node.right)
            max_dia = max(max_dia, left + right)

            return 1 + max(left, right) # return的值，若有回溯上一層時會用到

        dfs(root)
        return max_dia
            


