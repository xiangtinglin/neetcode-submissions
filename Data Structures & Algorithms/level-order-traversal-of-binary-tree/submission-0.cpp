/*
Ctrl + Shift + B：只編譯
clang++ .\Test.cpp -std=c++17 -g -Wall -Wextra -o .\Test.exe
.\Test.exe

*/

// #include <iostream>
// #include <vector>

// using namespace std;

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


/*
 [題目理解]
    # Given: the root of a binary tree
    # return: the level order traversal of its nodes' values
        ->> vector<vector<int>>
    # thoughts:
        1.return型式 ->> 要做BFS ->> 紀錄每回合left, right node總量(= 要pop幾個node)
            ->> container用 queue!(FIFO) & 每輪開始前算這層有幾個

*/

/*
 一、Breadth First Search(BFS)
    T:O(n) traverse the whole tree nodes
    S:O(w) for extra space, where w 是樹的最大寬度，也就是某一層最多的節點數。
      O(n) for worst case, 完整二元樹的最後一層可能包含大約 n/2 個節點

    # thoughts: 
        要做BFS ->> 紀錄每回合left, right node總量(= 要pop幾個node)
        ->> container用 queue!(FIFO) & 每輪開始前算這層有幾個
*/

// class Solution {
// public: 
//     vector<vector<int>> levelOrder(TreeNode* root) {
//         // 1.Initial- containers(queue, vector)
//         queue<TreeNode*> q;
//         vector<vector<int>> res;
//         if (!root) {return res;} // edge case
//         // 2.add all left/right nodes level by level(push root to queue first brfore starting)
//         q.push(root);
//         // 3.while loop:
//         int levelSize;
//         while (!q.empty()) { // container 不能用 while (q)
//             // (1)count the number of nodes in queue currently
//             levelSize = q.size();
//             vector<int> curV; // reset!
//             // (2)for loop:
//             for (int i = 0; i < levelSize; i++) {
//                 TreeNode* curN = q.front(); // get & pop & push into curV
//                 q.pop();
//                 curV.push_back(curN->val);
//                 // (3)push left/right nodes
//                 if (curN->left) {q.push(curN->left);}
//                 if (curN->right) {q.push(curN->right);}
//             }
//             // (4)push to res
//             res.push_back(curV);
//         }
//         // 3.return
//         return res;
//     }
// };



/*
 二、DFS（Depth First Search）
    T:O(n) for traversing every nodes
    S:O(h) for extra space, where h is the height of tree.(worst case- skewed: O(n))

    # thoughts: 從已經會的 BFS，推導為什麼 DFS 也能完成這題?
        1.BFS 和 DFS 缺少的資訊不同:
            BFS: level by level, 用queue可記錄 & 取得 q.size()
            DFS: 深度優先, 走到某 node 不知道要放哪層? ->> 做DFS時也攜帶depth資訊
                 ->> ex.
                        dfs(1, 0)
                        dfs(2, 1)
                        dfs(4, 2)
                        dfs(3, 1)
                      這樣即使 3 比 4 晚被拜訪，我們仍然知道：
                        4 應該放進 res[2], 3 應該放進 res[1]
        2.作法: DFS- 用recursion實作
            題目要求按「層」分組
                    ↓
            每一層就是一個 depth
                    ↓
            DFS 雖然不按層走，但可以攜帶 depth
                    ↓
            把 node->val 放進 res[depth]
*/

class Solution {
public:
    // struct TreeNode {
    //     int val;
    //     TreeNode *left;
    //     TreeNode *right;
    //     TreeNode() : val(0), left(nullptr), right(nullptr) {}
    //     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    //     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    // };

    vector<vector<int>> res; // dfs也要使用 ->> 宣告在公作用域
    vector<vector<int>> levelOrder(TreeNode* root) {
        // 1.call helper: DFS(recursion實作)
        dfs(root, 0); // 從root開始: 第0層 也對應vector[0]
        // 2.return
        return res;
    }

    // 重點在設計dfs recursion function!
    void dfs(TreeNode* node, int depth) { // 思考dfs需要傳入的參數 & 回傳什麼?
        // 1.if null(edge case || 到底)
        if (!node) {return;}
        // 2.先處理當前node: 對應vector[depth]是否存已在於res & push_back(val)
        if (depth == (int)res.size()) { // 注意: 判斷條件 & 初始為空
            res.push_back({});
        }
        res[depth].push_back(node->val);
        // 3.繼續: call left, right
        dfs(node->left, depth + 1);
        dfs(node->right, depth + 1);
        // 4.完成
        return;
    }
};


// int main() {
//     Solution sol;
//     typedef Solution::TreeNode TreeNode;

//     TreeNode* root = new TreeNode(3);
//     TreeNode* node9 = new TreeNode(9);
//     TreeNode* node20 = new TreeNode(20);
//     root->left = node9;
//     root->right = node20;
//     TreeNode* node15 = new TreeNode(15);
//     TreeNode* node7 = new TreeNode(7);
//     TreeNode* node4 = new TreeNode(4);
//     node9->left = node15;
//     node9->right = node7;
//     node20->left = node4;
//     node20->right = nullptr;

//     cout << "Binary tree structure:" << endl;
//     cout << "        " << root->val << endl;
//     cout << "       / \\" << endl;
//     cout << "      " << node9->val << "  " << node20->val << endl;
//     cout << "     / \\  / \\" << endl;
//     cout << "    " << node15->val << "  " << node7->val << " " << node4->val << " null\n" << endl;

//     cout << "Level order traversal of the binary tree:" << endl;
//     vector<vector<int>> result = sol.levelOrder(root);
//     for (const auto& level : result) {
//         for (int val : level) {
//             cout << val << " ";
//         }
//         cout << endl;
//     }

//     return 0;
// }