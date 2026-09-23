class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
class Solution:
    def isSameTree(self, p:Optional[TreeNode], q:Optional[TreeNode]) -> bool:
        ''' 策略：因True比較嚴苛、情況相對單純，用條件篩選後剩下就是False '''
        if not p and not q: # 結構同、都沒node
            return True
        if p and q and p.val == q.val:  # 結構同&數值同：接續比左/右子樹
            return self.isSameTree(p.left, q.left) and self.isSameTree(p.right, q.right)
        else:
            return False

        
