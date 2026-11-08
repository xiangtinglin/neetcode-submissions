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
 一、unordered_set
    T:O()
    S:O()
*/

class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node* q) {
        // 1.create unordered_set P
        unordered_set<Node*> setP; // 無須排序, 依據 q traverse parent ->> 用set最快
        Node* cur = p;
        while (cur != nullptr) {
            setP.insert(cur);
            cur = cur->parent;
        }
        // 2.traverse the ancestors of q to find the first node meet in unordered_set P
        cur = q;
        while (!setP.count(cur)) {
            cur = cur->parent;
        }
        // 3.return
        return cur;
    }
};