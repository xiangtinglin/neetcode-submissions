# definition for binary tree node
class TreeNode:
    def __init__(self, val=0, left=None, right=None):   # 跟ListNode差別是，TreeNode有2個「next（左&右）」
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def invertTree(self, root:Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return None # 回傳type是TreeNode，不是bool
        '''
        1.先左右交換(adrress)，再call自己
        2.可用Tuple Packing功能: root.left, root.right = root.right, root.left
        '''
        tmp = root.left
        root.left = root.right
        root.right = tmp

        self.invertTree(root.left)  # 先做左
        self.invertTree(root.right)

        return root


        
