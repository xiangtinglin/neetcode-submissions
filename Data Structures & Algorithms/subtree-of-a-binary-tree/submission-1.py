# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

'''延續上週'''
# 使用isSameTree（recursion）
class Solution:
    def isSubtree(self, root:Optional[TreeNode], subRoot:Optional[TreeNode]) -> bool:
        if not subRoot: # None算任何tree的subtree
            return True
        if not root and subRoot: # and subRoot也寫出來更清楚
            return False
        if self.isSameTree(root, subRoot):
            return True
        return self.isSubtree(root.left, subRoot) or self.isSubtree(root.right, subRoot)
    # 也可以寫進inner function（封裝性）
    def isSameTree(self, tree1:Optional[TreeNode], tree2:Optional[TreeNode]) -> bool:
        if not tree1 and not tree2:
            return True
        if tree1 and tree2 and tree1.val == tree2.val:
            return self.isSameTree(tree1.left, tree2.left) and self.isSameTree(tree1.right, tree2.right)
        else:
            return False


        