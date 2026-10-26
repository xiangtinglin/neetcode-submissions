// clang++ -Wall -Wextra -Werror -std=c++17 -o Test_int Test_int.cpp

// # include <iostream>
// # include <unordered_map>
// using namespace std;


/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

    # my note:
        1. 也可以用 struct，不一定用 class。 只是 LeetCode 提供的節點定義採用這個寫法.
        2. Node 為題目提供的名稱, 需配合。（也可自行命名）
        3. 用 _val 可區分:
            左邊 val：節點的成員變數。
            右邊 _val：呼叫建構子時傳進來的參數。
*/

/*
    Given: A linked list of length n
    Act: Construct a deep copy
    Return: the head of the copied linked list.
*/

/*
 1️⃣ Hash Map (Two Pass)- T:O(n); S:O(n)
    # thoughts:
        Pass 1: 
            Create a copy of every node (just values), and store the mapping: original_node → copied_node
        Pass 2: 
            Use this map to 「connect next and random pointers」 for each copied node.
*/

// class Solution {
// public:
//     Node* copyRandomList(Node* head) {
//         // 1. Create a hash map, mapping each original to its copied node.
//         unordered_map<Node*, Node*> oldToCopy;
//         oldToCopy[nullptr] = nullptr; // ⚠️
//         // 2-1. First pass: iterate through the original list
//         Node* cur = head;
//         while (cur != nullptr) {
//             Node* copy = new Node(cur->val);
//             oldToCopy[cur] = copy;
//             cur = cur->next;
//         }
//         // 2-2. Second pass: iterate again(set next、random)
//         cur = head; // ⚠️reset! 同作用域不能寫 Node* cur（重複宣告error）
//         while (cur != nullptr) {
//             Node* copy = oldToCopy[cur];
//             copy->next = oldToCopy[cur->next];
//             copy->random = oldToCopy[cur->random];
//             cur = cur->next;
//         }
//         return oldToCopy[head];
//     }
// };


/*
 1️⃣-2 Hash Map (One Pass)- T:O(n); S:O(n)
    # thoughts: 延續法1. Hash Map (Two Pass), 能不能走一次就好?
        -> 可以! 在第一次建立新Node 同時 紀錄(1)cur : copy (2)cur->random : copy->random
*/

// class Node {
// public:
//     int val;
//     Node* next;
//     Node* random;
    
//     Node(int _val) : val(_val), next(nullptr), random(nullptr) {}
// };

class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> NodeMap;
        NodeMap[nullptr] = nullptr; // ⚠️
        
        Node* cur = head;
        while (cur) {
            if (NodeMap.find(cur) == NodeMap.end()) { // ⚠️避免dupicate new Node
                NodeMap[cur] = new Node(cur->val); // new Node(val)回傳的是 Node*
            }
            if (NodeMap.find(cur->next) == NodeMap.end()) {
                NodeMap[cur->next] = new Node(cur->next->val);
            }
            if (!NodeMap.count(cur->random)) {
                NodeMap[cur->random] = new Node(cur->random->val);
            }
            Node* copy = NodeMap[cur]; // 方便簡短表示
            copy->next = NodeMap[cur->next];
            copy->random = NodeMap[cur->random];
            
            cur = cur->next; // ⚠️
        }
        return NodeMap[head];
    }
};



/*
 2️⃣ Space Optimized I（省去法1的Hash Map）- 交錯插入
    T:O(n); 
    S:O(1) for extra space. O(n) for the output.

    # thoughts: 如何省去空間, 拿掉 Map？（但仍需這功能）
        -> 怎麼紀錄/推算對應copy位址？ 
        -> 利用原有的Node欄位資訊 & 規律List相對位置（原A->copy(a)->原B->copy(b))
        =  推算出 copy狀態
*/

// class Solution {
// public:
//     Node* copyRandomList(Node* head) {
//         if (!head) {return nullptr;}
//         // 1. Interleave copy nodes. For each original node A, create a copy A' and insert it right after A.
//         Node* cur = head;
//         while (cur != nullptr) {
//             Node* copy = new Node(cur->val);
//             copy->next = cur->next; // ⚠️先接後面
//             cur->next = copy;
//             cur = cur->next->next;
//         }
//         // 2. Assign random pointers(copy->next部分, 後面unweave時才處理)
//         cur = head; // ⚠️don't redefinition!!!- Node* cur = head;
//         while (cur != nullptr) {
//             Node* copy = cur->next;
//             if (cur->random != nullptr) { 
//                 copy->random = cur->random->next; // 如果cur->random == nullptr, nullptr->next會有問題 -> 用if排除
//             } // 不需要特別寫else{}, 因為建構已初始化給nullptr
//             cur = cur->next->next;
//         }
//         // 3. Unweave the lists
//         Node* newHead = head->next;
//         cur = head; // ⚠️don't redefinition!!!- Node* cur = head;
//         while (cur != nullptr) {
//             Node* copy = cur->next;
//             cur->next = copy->next;
//             if (copy->next != nullptr) { // ⚠️
//                 copy->next = copy->next->next;
//             }
//             cur = cur->next; // ⚠️🔥 不是cur->next->next !!!因為前面已經更新cur->next = copy->next;
//         }
//         return newHead;
//     }
// };



/*
 3️⃣ Space Optimized II 借用Node欄位暫存資訊
    T:O(n); 
    S:O(1) for extra space. O(n) for the output.
    
    # thoughts: 除了相對定位再unweave, 還能如何記錄取得資訊?
        -> 用Node欄位.next .random 暫存紀錄
        -> 不是為了更快，而是「借用既有欄位保存資訊」
    # note:
        1. 想省額外容器時，檢查現有結構有沒有暫時可借用的欄位；
        2. 要覆蓋有用資訊時，先決定原值保存在哪裡、何時取回。
        3. only pointer manipulations — no extra arrays, no hash map.
*/

// class Solution {
// public:
//     Node* copyRandomList(Node* head) {
//         if (!head) {return nullptr;}
//         // 1.Create all copied nodes
//         Node* cur = head;
//         while (cur) {
//             Node* copy = new Node(cur->val); // (1)each original node A, create a copy A'.
//             copy->next = cur->random; // (2)先備份避免覆蓋: 用copy->n暫存cur->r;  
//             cur->random = copy; // (3)cur->r存copy; ⚠️還不能填入正式copy->random（因後續copy Node尚未建立完全）
//             cur = cur->next; //⚠️
//         } 
//         // 2.Fix random pointers of copies
//         cur = head;
//         Node* newHead = cur->random; // ⚠️先存newHead
//         while (cur != nullptr) {
//             Node* copy = cur->random; // 方便後續簡短表示
//             if (copy->next != nullptr) { //⚠️
//                 copy->random = copy->next->random; // (1)用前兩者取正式copy->r（cur->random被拿來推算, 這輪還能更新）
//             } else {copy->random = nullptr;} //⚠️🔥
//             cur = cur->next; //⚠️
//         }
//         // 3.最後同一輪: (1)restore original list & (2)Connect the copied list
//         cur = head;
//         while (cur) {
//             Node*copy = cur->random;
//             cur->random = copy->next; // (1)restore: 先還原當前正式cur->r
//             copy->next = (cur->next != nullptr) ? cur->next->random : nullptr; // ⚠️(2)Connect: 正式的copy->n用後面尚未還原的cur->n->r取得（這就是不能都用.random的原因）
//             cur = cur->next;
//         }
//         return newHead;
//     }
// };



/*
 4️⃣ Recursion + Hash Map- T:O(n); S:O(n)
    # thoughts:
        1.Recursion如何運作?: call到底(一直傳入head->next), 逐層回傳
        2.每一層要return什麼？-> 先了解函式本身在做什麼?: 
            -> 查表!🔥 {original : copy}, 不論是查next or random
        3. Recursion過程中, 如何實現 (1)new Node (2)紀錄Hash Map- next/random
*/

// class Solution {
// private:
//     unordered_map<Node*, Node*> nodeMap{{nullptr, nullptr}}; // ⚠️放func外面, 共用同一張表
//     // ⚠️🔥 賦值要放func內{}; 否則就走初始化! {{ , }}
// public:
//     Node* copyRandomList(Node* head) {
//         // 1.先檢查是否存在於map中: 存在就取用，不存在就處理(new/next/random)
//         if (head == nullptr) {return nullptr;}
//         if (nodeMap.count(head)) {return nodeMap[head];} // 可以用 .find()；這裡只想知道「Key 是否存在」，所以用 .count() 比較簡短。
//         // 2.處理不存在於map中
//         Node* copy = new Node(head->val); // (1)new & store copy
//         nodeMap[head] = copy;
//         copy->next = copyRandomList(head->next); // (2)交給函式判斷: 存在就取用，不存在就建立(沿 next遞迴 -> 確保依序遍歷所有節點, 不漏掉!)
//         copy->random = nodeMap[head->random]; // (3)走到此確保一定找得到 = 代表recursion到底, 每層都已走過new Node
//         return copy;
//     }
// };


// int main() {
//     Solution sol;
//     Node* head = new Node(7);
//     head->next = new Node(13);
//     head->next->next = new Node(11);
//     head->next->next->next = new Node(10);
//     head->next->next->next->next = new Node(1);

//     head->random = nullptr;
//     head->next->random = head;
//     head->next->next->random = head->next->next->next->next;
//     head->next->next->next->random = head->next;
//     head->next->next->next->next->random = head;

//     cout << "\nOriginal list:" << endl;
//     for (Node* cur = head; cur != nullptr; cur = cur->next) {
//         cout << "Node value: " << cur->val;
//         if (cur->random) {
//             cout << ", Random points to: " << cur->random->val << endl;
//         } else {
//             cout << ", Random points to: nullptr" << endl;
//         }
//     }

//     Node* copiedListHead = sol.copyRandomList(head);
//     // Print the copied list to verify
//     Node* cur = copiedListHead;

//     cout << "\nCopied list:" << endl;
//     while (cur) {
//         cout << "Node value: " << cur->val;
//         if (cur->random) {
//             cout << ", Random points to: " << cur->random->val << endl;
//         } else {
//             cout << ", Random points to: nullptr" << endl;
//         }
//         cur = cur->next;
//     }

//     return 0;
// }