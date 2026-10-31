/*
Ctrl + Shift + B：只編譯
clang++ .\Test.cpp -std=c++17 -g -Wall -Wextra -o .\Test.exe
.\Test.exe

*/

// #include <iostream>
// #include <stack>

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
 一、Reverse List- 
        (Where m is the length of l1 and n is the length of l2.)
        T:O(m + n); 因為先後reverse! 
        S:O(1) for extra; S:O(max(m, n)) for the output list
        
    # thoughts: 1.reverse 2.逐一new Node 給最終pointer指向
*/

// class Solution {
// public:
//     ListNode* reverseList(ListNode* head) {
//         // 1.Initialize- cur, prev
//         ListNode* cur = head;
//         ListNode* prev = nullptr;
//         ListNode* tmp;
//         // 2.While list has nodes remaining:
//             while (cur) {
//             tmp = cur->next; // (1)tmp store original(cur->next)
//             cur->next = prev; // (2)Update: cur->next
//             prev = cur; // (3-1)must first: moveforward prev
//             cur = tmp;// (3-2)then: move forward cur
//             }
//         // 3.Return newHead
//         return prev; // 注意!: 不是cur
//     }

//     ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
//         // 1.Reverse both linked lists
//         l1 = reverseList(l1);
//         l2 = reverseList(l2);
//         // 2.Initialize- head, carry
//         int carry = 0;
//         ListNode* prev = nullptr; // !!到時候要回傳的head, 先從最後nullptr開始走
//         // 3.While either list has nodes remaining or carry > 0:
//             while (l1 || l2 || carry) {
//                 int v1 = (l1) ? l1->val : 0;// (1)Get the values v1 and v2(notice!: length diff)
//                 int v2 = (l2) ? l2->val : 0;
                
//                 int total = v1 + v2 + carry; // (2)Compute total
//                 carry = total / 10; // (3)Update carry, value
//                 int value = total % 10 ;

//                 ListNode* curNode = new ListNode(value); // (3)Create a new node with value total % 10 and prepend it.
                
//                 curNode->next = prev; // (5)Update(move forward): curNode, prev, both list pointers.
//                 prev = curNode;
//                 l1 = (l1) ? l1->next : nullptr; // 注意!! 不能寫(l1->next) ? ;因為l1可能是nullptr, nullptr->next 會error
//                 l2 = (l2) ? l2->next : nullptr;
//             }
//         // 4.Return new head
//         return prev;
//     }
// };



/*
 二、Stack- 
        (Where m is the length of l1 and n is the length of l2.)
        T:O(m + n)
        S:O(m + n) for extra space; O(max(m, n)) for output

    # Follow up: Could you solve it without reversing the input lists?
        法1要先reverse -> 有辦法不做reverse?
            -> 有! -> 觀察 原題目: 從最右邊位數開始算(取出最後) 
            -> 符合LIFO -> Stack!
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

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // 1.Create: stack & Push all values from list onto stack
        stack<int> s1, s2;
        while (l1) {
            s1.push(l1->val); // !! vector才用.push_back()
            l1 = l1->next;   // !! update !!
        } 
        while (l2) {
            s2.push(l2->val);
            l2 = l2->next;
        }
        // 2.Initialize: head, carry
        int carry = 0;
        ListNode* prev = nullptr;
        // 3.While either stack is non-empty or carry > 0:
        while (!s1.empty() || !s2.empty() || carry) { // !!注意: stack是容器 -> 要.empty()
            int v1 = (!s1.empty()) ? s1.top() : 0; if (!s1.empty()) {s1.pop();} // (1)top & pop values from stack
            int v2 = (!s2.empty()) ? s2.top() : 0; if (!s2.empty()) {s2.pop();}// !!!注意: stack為空無法.top() -> 0替補; 記得.pop!!!
            
            int total = v1 +v2 + carry; // (2)Compute
            carry = total / 10;
            int value = total % 10; // 記得宣告!

            ListNode* curNode = new ListNode(value); // (3)Create a new node & prepend
            curNode->next = prev; // (4)Update: head, carry
            prev = curNode;
        }
        // 4.Return newHead
        return prev;  // return curNode; 也可 -> 但!注意宣告範圍、不能重複宣告等問題
    }
};



// int main() {
//     Solution sol;
//     typedef Solution::ListNode ListNode;

//     cout << "Test addTwoNumbers with stack:" << endl;
//     int x1, x2, x3;
//     int y1, y2;
//     cout << "Enter values for l1 (3 digits) and l2 (2 digits): " << endl;
//     cout << "input l1: ";
//     cin >> x1 >> x2 >> x3;
//     cout << "input l2: ";
//     cin >> y1 >> y2;
//     ListNode* l1 = new ListNode(x1, new ListNode(x2, new ListNode(x3, nullptr)));
//     ListNode* l2 = new ListNode(y1, new ListNode(y2, nullptr));

//     ListNode* result = sol.addTwoNumbers(l1, l2);
//     cout << "Result: ";
//     while (result) {
//         cout << result->val << " ";
//         result = result->next;
//     }

//     return 0;
// }