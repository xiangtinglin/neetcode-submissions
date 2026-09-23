# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        stack = [[root,1]]  # 存放 [node, 其所在的depth數值]
        max_depth = 0       # 紀錄depth最大值（初始化=0）
        
        while stack:    # 如果寫while root就♾️循環
            curr_node, curr_depth = stack.pop()
            max_depth = max(max_depth, curr_depth)    # 更新max_depth數值
            ''' 2個if，確保stack存放有效node，減少判斷過程（優於neetcode官方寫法）'''
            if curr_node.right:   
                stack.append([curr_node.right, curr_depth + 1])
            if curr_node.left:
                stack.append([curr_node.left, curr_depth + 1])

        return max_depth




