# Definition for a binary tree node.
# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def isBalanced(self, root:Optional[TreeNode]) -> bool:
        # 過程中，需要紀錄2個資訊-> 需要nested另一個函數並使用回傳值
        def dfs(node):
            if not node:
                return [True, 0] #沒node算平衡
            # note：回傳2個資訊[boolean, depth]
            left, right = dfs(node.left), dfs(node.right) # (1)
            balanced_bool = (left[0] and right[0]
                            and abs(left[1] - right[1]) <= 1)  # 1.&(2)
            return [balanced_bool, 1 + max(left[1], right[1])]
        return dfs(root)[0]  # ⚠️[0] 才是bool值
