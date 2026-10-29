/*
Ctrl + Shift + B：只編譯
clang++ .\Test.cpp -std=c++17 -g -Wall -Wextra -o .\Test.exe
.\Test.exe

*/

// #include <iostream>

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
    # Given: two non-empty linked lists representing two non-negative integers.
    # Act: Add the two numbers
    # Return: the sum as a linked list.
    # Note:
        1.The digits are stored in reverse order
        2.each of their nodes contains a single digit. 
        3.do not contain any leading zero

    # Constraints: The number of nodes in each linked list is in the range [1, 100].
        -> long long 無法存100位數值, 不能化成實際100位數加減
        -> 只能用Linked-List

*/

/*
 一、Iteration- 
    (Where m is the length of l1 and n is the length of l2.)
    Time complexity: 
        O(max(m,n)) 最多+1 (常數倍數可忽略)
    Space complexity:
        O(1) extra space. O(max(m,n)) for the output list.
    
    # thought:
        1.順序inverse + Linked-List(by digit) -> 模擬直式加法, 且順序剛好正確也是從個位數起算
            -> 需處理進位問題(carry)
        2.Edge case: l1、l2長度不同 -> 判斷補0
*/

// class Solution {
// public:
//     ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
//         // 1.Create:
//         ListNode* dummy =   new ListNode(); // 不用傳數值, 不會用到
//         ListNode* cur = dummy; // 存results

//         // 2.Calculate: Loop while l1 exists, l2 exists, or carry is non-zero:
//         int carry = 0; // !! 紀錄進位
//         int value;
//         while (l1 || l2 || carry) {
//             int v1 = (l1 != nullptr) ? l1->val : 0; // !!記得如果空要補0
//             int v2 = (l2 != nullptr) ? l2->val : 0;

//             int total = v1 + v2 + carry; // carry從0開始
//             carry = total / 10;
//             value = total % 10;
//             cur->next = new ListNode(value); // cur->next不用再宣告ListNode*

//             l1 = (l1 != nullptr) ? l1->next : nullptr; // 不能直接寫 l1 = l1->next;
//             l2 = (l2 != nullptr) ? l2->next : nullptr;
//             cur = cur->next; // !!!記得更新
//         }
//         ListNode* res = dummy->next;
//         delete dummy;
//         return res;
//     }
// };



/*
 二、Recursion- 
    T: O(max(m,n)) 最多+1 (常數倍數可忽略)
    S: O(max(m,n)) for the recursion call stack.
       O(max(m,n)) for the output list.
    # thoughts: 
        1.先找出重複做的部分
        2.定義recursion形式, 傳入什麼參數等等
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

    ListNode* rec(ListNode* l1, ListNode* l2, int carry) { // 注意!!!: 除了當層digit, 還要傳入前一層算出來的carry!
        if (!l1 && !l2 && carry == 0) {return nullptr;}

        int v1 = (l1) ? l1->val : 0;
        int v2 = (l2) ? l2->val : 0;
        
        int total = v1 + v2 + carry;
        int newCarry = total / 10; // 也可以不宣告, 沿用更新carry = 
        int value = total % 10;

        l1 = (l1) ? l1->next : nullptr;
        l2 = (l2) ? l2->next : nullptr;
        ListNode* nextNode = rec(l1, l2, newCarry);

        return new ListNode(value, nextNode);
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return rec(l1, l2, 0); // 一開始carry = 0
    }
};


// int main() {
//     Solution sol;

//     typedef Solution::ListNode ListNode;

//     int x1, x2, x3, y1, y2;
//     cout << "input 3 values for l1 and 2 values for l2" << endl;
//     cin  >> x1 >> x2 >> x3 >> y1 >> y2;
//     cout << "Input: l1 = [" << x1 << "," << x2 << "," << x3 << "], l2 = [" << y1 << "," << y2 << "]" << endl;
//     ListNode* l1 = new ListNode(x1, new ListNode(x2, new ListNode(x3)));
//     ListNode* l2 = new ListNode(y1, new ListNode(y2));

//     ListNode* result = sol.addTwoNumbers(l1, l2);
//     cout << "Output: [";

//     ListNode* temp = result;
//     while (temp) {
//         cout << temp->val;
//         if (temp->next) cout << ",";
//         temp = temp->next;
//     }
//     cout << "]" << endl;

//     return 0;
// }