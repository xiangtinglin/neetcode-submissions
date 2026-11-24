// clang++ .\Test.cpp -std=c++17 -o Test.exe
// .\Test.exe

#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>

using namespace std;


/*
 [理解題目]
    # Given: a reference of a node(in a connected undirected graph.)
    # Return:  a deep copy (clone) of the graph.(as a reference to the cloned graph.)

    # test format:
        1.each node's value is the same as the node's index (1-indexed)
        2.The given node will always be the first node with val = 1.
    # constraints:
        1.Node.val is unique for each node.
        2.There are no repeated edges and no self-loops in the graph.
        3.The Graph is connected and all nodes can be visited starting from the given node.

    # note:
        1.edge case:
            (1) adjList = [[]] 非空有node 但沒neibors; 
                adjList = [] 為空graph沒任何nodes
            (2) 有環 ->> 避免無限遞迴，最後造成 stack overflow。
                        ->> 需要記住哪些節點已經複製過
        2.確保一個原節點只對應一個新節點:
            新 Node 2 ─┐
                        ├→ 新 Node 3
            新 Node 4 ─┘
            ->> 因此需要透過記錄已處理的 map 找到已建立的新 Node 3。

    # thoughts:
        1. 先讀懂題目: 題目傳進來的不是 adjacency list, 是 node*
        2. 這題的核心不是「複製每個節點的數值」，而是： 一邊走訪原圖，一邊建立新節點，並正確重建所有節點之間的連線。
            ->> 需要記錄: 原節點地址 → 對應的新節點地址
        3. deep copy 必須滿足：
            1. 每個節點都是新建立的物件。
            2. 新圖中的 neighbors 只能指向新節點。
            3. 新圖的連接關係和原圖相同。
            4. 修改新圖不會影響原圖。
        4. ex:
            adjList = [[2,4], [1,3], [2,4], [1,3]]
                Node 1.neighbors = [Node 2, Node 4]
                Node 2.neighbors = [Node 1, Node 3]
                Node 3.neighbors = [Node 2, Node 4]
                Node 4.neighbors = [Node 1, Node 3]
        
*/



/*
 一、[Graph traversal（DFS）＋ visited map]
    T:  O(V + E) for total time.
        O(V) for create new node
        O(2 * E) for push neighbors(non-direction ->> keep both side neighbors)
    S:  O(V) for total extra space.
        O(V) for map
        O(V) for worst dfs(call stack)
    (Where V is the number of vertices and E is the number of edges.)

    # thoughts:
        1.「從一個節點找完整張圖」想到 DFS/BFS；「圖有環」想到 visited；「要複製」把 visited 升級成原節點到新節點的 map。
        2.Sol:
            DFS：用遞迴 stack 決定下一個處理誰
            BFS：用 queue 決定下一個處理誰
*/

/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/


// class Solution {
// public:
//     Node* cloneGraph(Node* node) {
//         // 1.Container, initial
//         unordered_map<Node*, Node*> visitedMap; // avoid dead loop & duplicat new node
//         // 2.Call helper func- dfs & return node* startCloneNode
//         return dfs(node, visitedMap);
//     }

// private:
//     // helper func- dfs
//     Node* dfs(Node* node, unordered_map<Node*, Node*>& visitedMap) { // 記得map要共用 ->> 加& (否則每次call func都會重新創建一個map沒延續保存)
//         // 1.if (!node)
//         if (node == nullptr) {return nullptr;}
//         // 2.if (node is in map)
//         if (visitedMap.count(node)) {
//             return visitedMap[node];
//         }
//         // 3.otherwise, (i)create new node (ii)store it in map (iii)recursively: clone all neighbors & push_back to clone's neighbor list
//         Node* copy = new Node(node->val);
//         visitedMap[node] = copy;
//         for (Node* nei : node->neighbors) {
//             copy->neighbors.push_back(dfs(nei, visitedMap));
//         }
//         // 4.return the clone's starting node*
//         return copy;
//     }
// };



/*
 二、[Graph traversal（BFS）＋ queue]
    T:  O(V + E) for total.
        O(V) for create new clone node
        O(2 * E) for push all neighbors(non-direction)
    S:  O(V) for total extra space.
        O(V) for queue the worst
        O(V) for map
    (Where V is the number of vertices and E is the number of edges.)  
*/

// class Node {
// public:
//     int val;
//     vector<Node*> neighbors;
//     Node() {
//         val = 0;
//         neighbors = vector<Node*>();
//     }
//     Node(int _val) {
//         val = _val;
//         neighbors = vector<Node*>();
//     }
//     Node(int _val, vector<Node*> _neighbors) {
//         val = _val;
//         neighbors = _neighbors;
//     }
// };

class Solution {
public:
    Node* cloneGraph(Node* node) {
        // 1.Container, inital: visited map
        unordered_map<Node*, Node*> visitedMap;
        // 2.Call helper func- BFS & return the clone's starting node*
        return bfs(node, visitedMap);
    }

private:
    Node* bfs(Node* node, unordered_map<Node*, Node*>& visitedMap) { // 注意!map要共用延續進度 ->> 加&
        // 1.Container, inital: queue
        queue<Node*> q;
        // 2.if (!node)
        if (!node) {return nullptr;} // edge case!
        // 3.Create clone & store in map for the starting node
        Node* copy = new Node(node->val);
        visitedMap[node] = copy;
        // 4.Start BFS from the given node(while...)
        q.push(node); // 注意: 不是copy
        while (!q.empty()) {
            // (1)get & pop the queue
            Node* curN = q.front();
            q.pop();
            // (2)for each neighbor: (i)if (not cloned yet) {clone new node & store in map} (ii)then push neighbors to queue & clone's neighbors list
            for (Node* nei : curN->neighbors) {
                if (visitedMap.find(nei) == visitedMap.end()) {
                    visitedMap[nei] = new Node(nei->val);
                    q.push(nei); // 注意: not cloned才要push ->> 否則會over time
                }
                visitedMap[curN]->neighbors.push_back(visitedMap[nei]);
            }
        }
        // 5.return the clone's starting node
        return copy;
    }
};



// int main() {
//     Solution sol;
    
//     Node* node1 = new Node(1);
//     Node* node2 = new Node(2);
//     Node* node3 = new Node(3);
//     Node* node4 = new Node(4);
//     Node* node5 = new Node(5);
//     node1->neighbors = {node2, node4};
//     node2->neighbors = {node1, node3};
//     node3->neighbors = {node2, node4};
//     node4->neighbors = {node1, node3};
//     node5->neighbors = {node1, node2};
//     cout << "Original Graph:" << endl;
//     for (int i = 1; i <= 5; i++) {
//         Node* node = (i == 1) ? node1 : (i == 2) ? node2 : (i == 3) ? node3 : (i == 4) ? node4 : node5;
//         cout << "Node " << node->val << " neighbors: ";
//         for (Node* neighbor : node->neighbors) {
//             cout << neighbor->val << " ";
//         }
//         cout << endl;
//     }

//     Node* afterClone = sol.cloneGraph(node1);
    
//     cout << endl;
//     cout << "[original starting node]:" << node1 << ", value: " << node1->val << endl;
//     cout << "[afterClone starting node]:" << afterClone << ", value: " << afterClone->val << endl;

//     return 0;
// }