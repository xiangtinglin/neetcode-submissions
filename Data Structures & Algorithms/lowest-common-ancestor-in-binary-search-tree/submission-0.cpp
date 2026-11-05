/*
Ctrl + Shift + B：只編譯
clang++ .\Test.cpp -std=c++17 -g -Wall -Wextra -o .\Test.exe
.\Test.exe

*/

// #include <iostream>

// using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {} // Instance = constructor : Member Initializer List {cout << "TreeNode created\n";}
 * };
 */

/*
 [題目理解]
    # Given:  a binary search tree (BST),  two nodes p and q.
    # Act: find the lowest common ancestor (LCA) node of two given nodes in the BST.
    # Definition of LCA: ...(where we allow a node to be a descendant of itself).
    
    # Core thoughs: BST 解法不必先找到 p 和 q，也不必儲存 parent 或完整路徑。

    # Note:
        1.Constraints: All Node.val are unique. ->> 沒有重複值，這題可以直接使用嚴格不等式
        2.結合BST性質: 左子樹所有值 < 目前節點值 < 右子樹所有值
        3.p != q
    
    # 延伸概念:
        1.tree種類, ex:
            (1)Binary Tree：只規定每個 node 最多兩個 child
            (2)BST：Binary Tree + 特定的數值排序規則 (無重複值時是「左小右大」；允許重複值時，重複值的處理方式由資料結構的設計規則決定。)
        2.特殊案例:
            p = 5, q = 5, ans = 2
                  6
                /   \
               2     8
              / \
             0   4
                / \
               3   5
        3.題目範例: root = [6,2,8,0,4,7,9,null,null,3,5]
            不是直接傳進函式的 C++ vector，而是 LeetCode 用來描述／序列化 Tree 結構的格式。
*/


/*
 一、Iteration(not brute force)- T:O(log n) = h樹高度; S:O(1) for extra space
    # thoughts:
        base on the features of BST & All Node.val are unique. 
        ->> follow the clear rules(< cur, > cur, otherwise(一大一小)) to search for the position of ancestor node
*/


// class Solution {
// public:
//     // // 1.Create & initialize
//     // struct TreeNode {
//     //     int val;
//     //     TreeNode* left;
//     //     TreeNode* right;

//     //     TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
//     // }

//     TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//         TreeNode* cur = root;

//         while (cur) {
//             if (p->val < cur->val && q->val < cur->val) {
//                 cur = cur->left;
//             } else if (p->val > cur->val && q->val > cur->val) {
//                 cur = cur->right;
//             } else {
//                 return cur;
//             }
//         }
//         return nullptr;
//     }
// };



/*
 二、Recursion- T:O(h); S:O(h) the height of tree
    # thoughts: 重複步驟recursion化
*/

// struct TreeNode {
//     int val;
//     TreeNode* left;
//     TreeNode* right;

//     TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
// };

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* cur = root;

        if (p->val < cur->val && q->val < cur->val) {
            cur = cur->left;
        } else if (p->val > cur->val && q->val > cur->val) {
            cur = cur->right;
        } else {
            return cur;
        }
        return lowestCommonAncestor(cur, p, q);
    }
};

// int main() {
//     // Example usage:
//     TreeNode* root = new TreeNode(6);
//     root->left = new TreeNode(2);
//     root->right = new TreeNode(8);
//     root->left->left = new TreeNode(0);
//     root->left->right = new TreeNode(4);
//     root->right->left = new TreeNode(7);
//     root->right->right = new TreeNode(9);
//     root->left->right->left = new TreeNode(3);
//     root->left->right->right = new TreeNode(5);

//     cout << "Example usage:" << endl;
//     cout << "Tree structure:" << endl;
//     cout << "        6" << endl;
//     cout << "       / \\" << endl;
//     cout << "      2   8" << endl;
//     cout << "     / \\ / \\" << endl;
//     cout << "    0  4 7 9" << endl;
//     cout << "      / \\" << endl;
//     cout << "     3   5" << endl;

//     Solution solution;
//     TreeNode* p = root->left; cout << "Node p: " << p->val << endl; // Node with value 2
//     TreeNode* q = root->left->right; cout << "Node q: " << q->val << endl; // Node with value 4

//     TreeNode* ans = solution.lowestCommonAncestor(root, p, q);
//     if (ans) {
//         cout << "Lowest Common Ancestor: " << ans->val << endl;
//     } else {
//         cout << "Lowest Common Ancestor not found." << endl;
//     }

//     // Clean up memory (not shown for brevity)
//     return 0;
// }