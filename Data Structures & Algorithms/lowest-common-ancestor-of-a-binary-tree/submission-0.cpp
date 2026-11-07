/*
Ctrl + Shift + B：只編譯
clang++ .\Test.cpp -std=c++17 -g -Wall -Wextra -o .\Test.exe
.\Test.exe

*/

// #include <iostream>
// #include <vector>
// #include <unordered_map>
// #include <unordered_set>
// #include <queue>

// using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*
 [題目理解]
    # Given: a binary tree, node* p, node* q.
    # Act:  find the lowest common ancestor (LCA) of two given nodes in the tree.

    # Note:
        1.和前面做的 235. LCA of a Binary Search Tree 最大差異是：
            - 235 是 BST，可以利用「左小右大」判斷方向。
            - 236 只是普通 Binary Tree，沒有大小規則，所以必須實際搜尋左右子樹。
    # thoughts:
        1.最直覺的方法：記錄兩條路徑 ->> 取最後一個相同的node* ->> 但時間複雜度是 O(n)，需要額外儲存路徑。

*/

/*
    一、雙路徑法(個人解)- 
        T:O(n);
        S:O(h), where h is the tree height, and it becomes O(n) in the worst case(Skewed).

        # thoughts:
            任務 A：找出 root → target 的路徑(dfs)
            任務 B：比較 p、q 的路徑，找最後一個共同節點, ex: path1 = {2, 4}; path2 = {2, 4, 3, 5};
*/

// class Solution {
// public:
//     // 1.先寫主函式
//     TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//         // (1)Container
//         vector<TreeNode*> pathP;
//         vector<TreeNode*> pathQ;
//         // (2)建構出root到p、q path- 另寫helper func
//         findPath(root, p, pathP); // !只要執行函式，無須保存它回傳的 bool & 題目確保p, q必存於Tree
//         findPath(root, q, pathQ);
//         // (3)while loop through pathP & pathQ to find the final same node
//         TreeNode* lca;
//         int i = 0;
//         while (i < pathP.size() && i < pathQ.size() && pathP[i] == pathQ[i]) {
//             lca = pathP[i];
//             ++i;
//         }
//         return lca;
//     }
//     // 2.寫主函式時, 發現需要helper ->> 任務A: 找目標node路徑函式(主函式需要的是path過程, 非return什麼)
//     bool findPath(TreeNode* root, TreeNode* target, vector<TreeNode*>& path) { // target只找單1個
//         if (root == nullptr) {return false;}

//         path.push_back(root); // 先push
//         if (root == target) {return true;} // 關鍵檢查! 還不能else {return flase;} !!!
//         // root != target, 才會繼續找!
//         if (findPath(root->left, target, path) || findPath(root->right, target, path)) {
//             return true;
//         } else {
//             path.pop_back(); // recursion目前這一支已最底(左右都nullptr), 才到這行. pop_back代表traceback繼續探索找
//             return false; // 記得
//         }
//     }
// };



/*
 二、DFS (Boolean Tracking)
    T:O(n); 
    S:O(h), where h is the height of BSTree, and O:(n) is the worst cases(skewed).

    # thoughts:
        1.goal: 改善雙路徑法
            雙路徑法： DFS 找 p → DFS 找 q → 比較路徑
            Boolean Tracking： 一次 DFS 同時確認每棵子樹是否包含 p、q
        2.LCA 真正需要知道的是： 哪一個最低的節點，其子樹同時包含 p 和 q？
            ->> 不一定需要完整的雙路徑： root->p, root-q
            ->> 改成讓每個節點回報y/n：子樹有沒有 p？ 子樹有沒有 q？ ->> pair<bool, bool>
            ->> 最後回傳最低(第一次符合條件)的ancestor node*
*/

// class Solution {  
// public:
//     // # 主程式
//     TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//         lca = nullptr; // reset!(若主函式被call多次避免殘留覆蓋) & 初始化nullptr, 後面判斷是不是最低會用到
//         // 1.DFS中找到lca
//         dfs(root, p ,q); // 回傳值{bool, bool}用於helper判斷, 無須賦值回主函式
//         // 2.回傳lca
//         return lca;
//     }

// private:
//     TreeNode* lca; // 記得宣告在公作用域
//     // # helper- dfs()
//     pair<bool, bool> dfs(TreeNode* node, TreeNode* p, TreeNode* q) {
//         if (!node) {return {false, false};}

//         // 1.從root開始, 一次DFS(左右中)- pair<boolP, boolQ>
//         pair<bool, bool> left = dfs(node->left, p, q); // dfs在helper寫
//         pair<bool, bool> right = dfs(node->right, p, q);
        
//         bool foundP = left.first || right.first || node == p;
//         bool foundQ = left.second || right.second || node == q;

//         if (foundP && foundQ && lca == nullptr) { //必須要檢查 lca == nullptr, 代表遞迴中符合條件&第一個賦值(最低)!
//             lca = node;
//         }
//         return {foundP, foundQ}; // 記得reuturn有沒有找到p, q的結果!!!
//     }
// };



/*
 三、DFS(Optimal)
    T:O(n)
    S:O(h), where h is the height of tree and O:(n) is the worst case(skewed).

    # thoughts:
        1.差別
            Boolean Tracking： 回傳 {有沒有 p, 有沒有 q}, 並用成員變數 lca 保存答案
            Optimal DFS： 直接回傳找到的 p、q 或 LCA, 不需要 pair，也不需要成員變數
        2.優化關鍵: 不只能回報「有沒有找到」，還可以直接回報「找到哪個節點」
            ex.
                Boolean Tracking	改成 TreeNode*
                {false,false}	       nullptr
                {true,false}	          p
                {false,true}              q
                {true,true}	           LCA 節點
        3.不需要另外寫 helper，主函式本身就是 recursive function：
        4.優化點:
            Boolean Tracking 的 Big-O 相同，但：
            - 程式碼更短。
            - 不需要 pair。
            - 不需要成員變數 lca。
            - 答案直接由 recursive return 傳回。
            - 通常是這題最推薦的寫法。
*/

// class Solution {
// public:
//     // 主程式本身就做recursion
//     TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//         // 1.先檢查當前root
//         if (!root || root == p || root == q) {return root;}
//         // 2.展開root->left, right
//         TreeNode* left = lowestCommonAncestor(root->left, p , q);
//         TreeNode* right = lowestCommonAncestor(root->right, p , q);
//         // 3.Check: left, right
//         // (1)左右都有結果: root
//         if (left != nullptr && right != nullptr) {return root;}
//         // (2)剩下cases: l or r(都沒,傳r 也是nullptr)
//         return (left != nullptr) ? left : right;
//     }
// };



/*
 四、BFS + Parent Map
    T:O(n), 走訪每個nodes
        BFS 最多走訪所有節點：\(O(n)\)
        從 p 往上：\(O(h)\)
        從 q 往上：\(O(h)\)
    S:O(n), unordered_map 最多放所有節點：
        Ancestors set：最多 O(h)
    # thoughts:
        1.方法的價值：
            - 不使用 recursion。
            - 補上「從子走回父」的能力。
        2.TreeNode有left, right, 可從parent-child ->> 但無法從 p, q 往上找到祖先
            ->> 因此要建立 Map 紀錄 child → parent, 之後便可依序查表往上
        3.steps:
            階段 1：BFS 建立每個節點的 parent
            階段 2：從 p 往上，把 p 的所有祖先放進 set
            階段 3：從 q 往上，找到第一個也屬於 p 祖先的節點
*/


// struct TreeNode {
//     int val;
//     TreeNode *left;
//     TreeNode *right;
//     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
// };

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 1.initial: 建立Map 紀錄 {child:parent} & BFS queue
        unordered_map<TreeNode*, TreeNode*> parentMap;
        queue<TreeNode*> nodesQ; // FIFO

        parentMap[root] = nullptr; // root往上沒parent
        nodesQ.push(root);
        // 1-2.直到p, q的都被找到 & 紀錄(map & 進queue)
        while (!parentMap.count(p) || !parentMap.count(q)) {
            TreeNode* cur = nodesQ.front(); // 取出
            nodesQ.pop(); // !好習慣: 先丟 

            if (cur->left != nullptr) {
                parentMap[cur->left] = cur;
                nodesQ.push(cur->left);
            }
            if (cur->right != nullptr) {
                parentMap[cur->right] = cur;
                nodesQ.push(cur->right);
            }
        }
        // 2.找到 p 並記錄: p -> root所有node(ancestorP)
        unordered_set<TreeNode*> ancP; // 順序不是靠set, 而是查parent

        TreeNode* cur = p;
        while (cur != nullptr) {
            ancP.insert(cur);
            cur = parentMap[cur];
        }
        // 3.找到 q 並往上找到第一個跟 p 共享node
        cur = q; // !不能重複宣告 TreeNode* cur =
        while (!ancP.count(cur)) {
            cur = parentMap[cur];
        }
        // 4.return
        return cur;
    }
};


// int main() {
//     Solution sol;
//     TreeNode* root = new TreeNode(3);
//     root->left = new TreeNode(5);
//     root->right = new TreeNode(1);
//     root->left->left = new TreeNode(6);
//     root->left->right = new TreeNode(2);
//     root->right->left = new TreeNode(0);
//     root->right->right = nullptr;
//     root->left->right->left = new TreeNode(7);
//     root->left->right->right = new TreeNode(4);

//     cout << "Binary Tree:" << endl;
//     cout << "        3" << endl;
//     cout << "       / \\" << endl;
//     cout << "      5   1" << endl;
//     cout << "     / \\ / \\" << endl;
//     cout << "    6  2 0  null" << endl;
//     cout << "      / \\" << endl;
//     cout << "     7   4" << endl;
    
//     TreeNode* p = root->right; // Node with value 1
//     TreeNode* q = root->right->left; // Node with value 0
//     TreeNode* lca = sol.lowestCommonAncestor(root, p, q);

//     cout << "Finding LCA of nodes with values: " << p->val << " and " << q->val << endl;
//     cout << "Lowest Common Ancestor: " << lca->val << endl;
    
//     return 0;
// }