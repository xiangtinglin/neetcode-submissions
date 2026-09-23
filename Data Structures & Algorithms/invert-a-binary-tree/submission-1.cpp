/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
 
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return nullptr;

        // 遞迴反轉左右子樹，並將結果保存下來
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);
        
        // 交換左右子節點（原地修改，不創建新節點省空間）
        root->left = right;
        root->right = left;
        
        return root;
    }
};
