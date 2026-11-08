/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

/*
 [題目理解]
    # Given: two nodes of a binary tree p and q
    # return: their lowest common ancestor (LCA).
    # thoughts:
        1.類似題型: 236. Lowest Common Ancestor of a Binary Tree
            ->> 差別: 這題有 Node* parent;
        2.bottom-up & 不需要提供root
*/

/*
 一、Hash Set(unordered_set)
    T:O(h), where h is the height of tree and worst case(skewed) is O(n).
    S:O(h), where h is the height of tree and worst case(skewed) is O(n).
*/

// class Solution {
// public:
//     Node* lowestCommonAncestor(Node* p, Node* q) {
//         // 1.create unordered_set P
//         unordered_set<Node*> setP; // 無須排序, 依據 q traverse parent ->> 用unordered_set最快
//         Node* cur = p;
//         while (cur) {
//             setP.insert(cur);
//             cur = cur->parent;
//         }
//         // 2.traverse the ancestors of q to find the first node meet in unordered_set P
//         cur = q;
//         while (cur) {
//             if (setP.count(cur)) {return cur;}
//             cur = cur->parent;
//         }
//         // 3.return
//         return nullptr;
//     }
// };


/**
 二、Iteration I
    T:O(h) where h is height of tree and worst case: O(n)
    S:O(1) for extra space

    # thoughts:
        1.how to avoid using extra space for a hash set?
            ->> 不用 Set，先個別計算 h 再對齊深度，再同步往上走
            ->> 寫一個 helper func 計算 h
*/

// class Solution {
// public:
//     Node* lowestCommonAncestor(Node* p, Node* q) {
//         // 1.計算 h1, h2
//         int h1 = height(p); // call helper
//         int h2 = height(q);
//         // 2.compare & align
//         Node* curP = p, * curQ = q; // 注意後者宣告也要*

//         while (h1 != h2) {
//             if (h1 > h2) {
//                 curP = curP->parent;
//                 --h1;
//             }
//             if (h1 < h2) {
//                 curQ = curQ->parent;
//                 --h2;
//             }
//         }
//         // 3.find the first same ancestor node
//         while (curP != curQ) {
//             curP = curP->parent;
//             curQ = curQ->parent;
//         }
//         // 4.
//         return curP; // curP, curQ都行
//     }
//     // # helper func
//     int height(Node* target) {
//         int h = 0;
//         Node* cur = target;
//         while (cur != nullptr) {
//             cur = cur->parent;
//             ++h;
//         }
//         return h;
//     }
// };



/*
 三、Iteration II(linked list intersection)
    T:O()
    S:O()

    # thoughts:
        1.Iteration I 核心問題: p, q 到 LCA 前的路程可能不同，所以須消除差異。
        2.把樹轉換成兩條 linked list ->> 找第一個交點
            8 → 7 → 2 ┐
                      ├→ 3 → 5 → nullptr
            1 ────────┘
        3.如何不算高度就消除差距??
            ->> 各自路徑長 h1 + h2 = H (總長都一樣)
            ->> 短的會先走完後走長的
            ->> 最後相遇會在 lca, 剩下路徑重疊
*/

class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node* q) {
        // 1.各自走路徑, 短的到root後, 繼續走另一個長的 ->> 直到第一個meet node
        Node* curP = p, * curQ = q;
        while (curP != curQ) {
            curP = (curP) ? curP->parent : q;
            curQ = (curQ) ? curQ->parent : p;
        }
        // 2.return lca;
        return curP;
    }
};