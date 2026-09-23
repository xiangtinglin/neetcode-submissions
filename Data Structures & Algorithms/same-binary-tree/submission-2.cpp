/**
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {};
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {};
    TreeNode(int x, TreeNode *left, TreeNode *right): val(x), left(left), right(right) {};
};
*/
class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        // 策略——Iteration（dfs）:T的前提（需比對完每個node才算對），先建立stack存放，之後跑stack內node
        stack<pair<TreeNode*, TreeNode*>> stk;
        stk.push( {p, q} );
        while (!stk.empty()) {
            auto [node_1, node_2] = stk.top();
            stk.pop();

            if (!node_1 && !node_2) {
                continue; //⚠️不能直接return True！！！❌跟recursion不同，一旦return就會退出while迴圈，可能提前結束
            }
            //至少一個null或數值不同，則flase
            if ( !node_1 || !node_2 || node_1->val != node_2->val) {
                return false;
            }
            stk.push( {node_1->left, node_2->left});
            stk.push( {node_1->right, node_2->right});
        }
        return true; //通過考驗，跳出迴圈
    }
};