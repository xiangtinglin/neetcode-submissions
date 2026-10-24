// clang++ -Wall -Wextra -Werror -std=c++17 -o Test_int Test_int.cpp

// # include <iostream>
// using namespace std;


/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

/*
    Given: the head of a linked list
    Act: remove the nth node from the end
    Return: its head.
*/


/*
 1️⃣ Brute Force- T:O(n); S:O(n)
    # 核心:
        1. Linked List沒辦法定位 -> 用vector逐一存ptr
        2. the index to remove: len(nodes) - n
        3. 不用真的remove, 略過接線即可 -> [index - 1].next = [index].next
*/

// class Solution {
// public:
//     ListNode* removeNthFromEnd(ListNode* head, int n) {
//         if (!head) {return nullptr;}
//         // Traverse the linked list and push every node ptr into an array. -> 取得index定位
//         vector<ListNode*> vec;
//         ListNode* cur = head;
//         while (cur != nullptr) {
//             vec.push_back(cur);
//             cur = cur->next;
//         }
        
//         int nums = vec.size();
//         int removeIndex = nums - n;
//         if (removeIndex == 0) {return head->next;}
//         else {
//             vec[removeIndex - 1]->next = vec[removeIndex]->next; // 可寫vec[removeIndex - 1], 因前面if保證removeIndex > 0; 不能寫 = vec[removeIndex + 1] , 可能超出範圍不存在vec！！！
//         }
//         return head;
//     }
// };


/*
 2️⃣ Iteration (Two Pass)- T:O(n); S:O(1)
    # thoughts: 
        如何省掉vector空間, 但保留功能(1)總個數(2)目標node定位？
        -> 第一次遍歷算總數 + 第二次走到remove前一個node(略過目標node往後接線)
*/

// class Solution {
// public:
//     ListNode* removeNthFromEnd(ListNode* head, int n) {
//         if (!head) {return nullptr;}

//         // 1. 第一次遍歷算總數
//         ListNode* cur = head;
//         int nums = 0;
//         while (cur != nullptr) {
//             nums++;
//             cur = cur->next;
//         }
//         // 2. 第二次走到remove前一個node(略過目標node往後接線)
//         int removeIndex = nums - n;
//         if (removeIndex == 0) {return head->next;} // 記得先處理特殊情況
//         else {
//             ListNode* cur = head; // 記得reset
//             for (int i = 0; i < removeIndex - 1; i++) { // ⚠️從head 走到移除的「前一個」要走幾圈loop -> 記得removeIndex - 1
//                 cur = cur->next;
//             }
//             cur->next = cur->next->next;
//         }
//         return head;
//     }
// };


/*
 3️⃣ Two pointers（one pass）- T:O(n); S:O(1)
    # thoughts: 
        法2. iteration須先算長度，才能推算位置 -> 有何方法，不算長度，也能定位？
        -> 不用推算定位 int removeIndex = nums - n;
        -> 指標抵達 nullptr 時，落在前 n 步的位置 = 移除目標
        -> 用nullptr定點 +「兩個指標維持固定距離」= 得知相對位置(不用知道具體index)
*/

class Solution {
public:
    // struct ListNode {
    //     int val;
    //     ListNode *next;
    //     ListNode() : val(0), next(nullptr) {}
    //     ListNode(int x) : val(x), next(nullptr) {}
    //     ListNode(int x, ListNode *next) : val(x), next(next) {}
    // };

    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (!head) {return nullptr;}

        // 1.建立two pointers
        ListNode dummy(0, head); // 沒prev -> 找要移除的前一個(l要從前一個出發)
        ListNode* l = &dummy; // ⚠️記得用「&」, dummy是物件不是ptr
        ListNode* r = head;
        // 2. Move right forward n steps.(固定距離回推l 為移除target node前一個)
        while (n > 0) {
            r = r->next;
            n--;   
        }
        // 3. Move both until right reaches the end.(nullptr)
        while (r != nullptr) {
            r = r->next;
            l = l->next;
        }
        l->next = l->next->next; // 略過target node

        return dummy.next; // ⚠️dummy是物件不是ptr, 不要用dummy->next
    }
};


/*
 4️⃣ Recursion- T:O(N); S:O(N) for recursion stack.

    # thoughts:
        題目要「倒數」，但沒prev 
        -> 遞迴雖不會多出 prev，卻可保留前面每一層的執行狀態。走到尾端後，再逐層返回.
        -> 返回時遇到的第n個節點，就是倒數第n個。
*/

// class Solution {
// public:
//     ListNode* removeNthFromEnd(ListNode* head, int n) {
//         return rec(head, n); // 都交由recursion處理
//     }

//     ListNode* rec(ListNode* head, int& n) { // ⚠️🔥 必須宣告且傳入 int& , 否則逐層會各自宣告多次新變數n, 到底回傳後的n不會累-（不同物件）
//         if (!head) {return nullptr;}
//         // 1.先一路傳到底, 直到head走到nullptr回傳後 -> 逐層處理(從最後一個node開始)
//         head->next = rec(head->next, n); // 從 head->next = nullptr開始
//         n--;    // 返回時才會開始-
//         if (n == 0) { // n = 0時, 當前head就是要除的目標node
//             return head->next; // 找到目標後, 略過自身傳回上一層使用
//         }
//         return head; // 一般都是回傳當前head回前一層, 維持正確指向
//     }
// };


// int main() {
//     int n;
//     int x1, x2, x3, x4, x5;

//     while (true) {
//         cout << "input n (1-5): ";
//         cin >> n;

//         if (n >= 1 && n <= 5) {
//             break;  // 合法，離開迴圈
//         }

//         cout << "輸入錯誤，n 必須在 1～5，請重新輸入。\n";
//     }

//     cout << "input 5 values: ";
//     while (true) {
//         cin >> x1 >> x2 >> x3 >> x4 >> x5;

//         if (cin.fail()) {
//             cout << "輸入錯誤，請輸入整數。\n";
//             cin.clear(); // 清除錯誤狀態
//             cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 忽略剩餘輸入
//             continue; // 重新輸入
//         }

//         break; // 輸入合法，離開迴圈
//     }

//     Solution sol;
//     using ListNode = Solution::ListNode;

//     // 建立linked list
//     ListNode node5(x5, nullptr);
//     ListNode node4(x4, &node5);
//     ListNode node3(x3, &node4);
//     ListNode node2(x2, &node3);
//     ListNode node1(x1, &node2);

//     ListNode* head = &node1;

//     ListNode* result = sol.removeNthFromEnd(head, n);

//     cout << "result: ";
//     while (result != nullptr) {
//         cout << result->val << " ";
//         result = result->next;
//     }
//     cout << endl;

//     return 0;
// }