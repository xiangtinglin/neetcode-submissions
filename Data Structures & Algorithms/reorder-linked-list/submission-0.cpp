// clang++ -Wall -Wextra -Werror -std=c++17 -o Test_int Test_int.cpp

// # include <iostream>
// # include <vector>
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
    # Given: the head of a singly linked-list
    # Operation: Reorder the list
    # Rule: not modify the values
    # Return: None!!!(函式void)

    # My thoughts:
      1. linked-list -> 改指向
      2. 只給head -> 靠pointer一個個走 -> 不能index[] 直接定位 -> 用Vector<ListNode*>存指向Nodes的指標!
 */


 /*
    一、Brute Force- T:O(n); S:O(n)
        Brute Force（暴力法）沒有規定一定要是 O(n²) 或很慢。 它描述的是解題方式：直接按照需求處理，沒有特別利用更深入的性質來優化。
        
        這份參考解法把陣列法叫做 Brute Force，是比較寬鬆的命名。稱為「陣列輔助法」其實更清楚。
        它的做法很直接：
        1. 不方便直接取得尾端節點？先把所有節點指標存進陣列。
        2. 再用左右索引，依照題目要求重新接線。

        後面的解法主要優化的是空間，時間仍然是 O(n)。
 */

// class Solution {
// public:
//     // // Definition for singly-linked list.
//     // struct ListNode {
//     //     int val;
//     //     ListNode *next;

//     //     ListNode() : val(0), next(nullptr) {}
//     //     ListNode(int x) : val(x), next(nullptr) {}
//     //     ListNode(int x, ListNode *next) : val(x), next(next) {}
//     // };

//     void reorderList(ListNode *head) {
//         if (!head) {return;} // 處理串列無任何node

//         vector<ListNode*> nodesPtrV; // 建立vector存pointer -> 就可以直接指定index[]
//         ListNode* cur = head;
//         while (cur) {
//             nodesPtrV.push_back(cur);
//             cur = cur->next;
//         }

//         int i = 0, j = nodesPtrV.size() - 1;
//         while (i < j) { // == 不要做! -> 否則會繞回變成circular! 
//             nodesPtrV[i]->next = nodesPtrV[j]; // l -> r照順序
//             i++;
//             if (i >= j) {break;} // 必須!!!檢查是否i >= j -> 立刻break! 否則會circular!!!(結束時一定有 i == j，不會出現 i > j)
//             nodesPtrV[j]->next = nodesPtrV[i];
//             j--;
//         }
//         nodesPtrV[j]->next = nullptr;
//     }
// };



/*
    二、(partition first) Reverse And Merge- T:O(n); S:O(1)
        # My thoughts:
            1. 如果不用法1開vecotr用index直接定位 -> linked list 沒有提供索引 l、r，也不能用 head[mid] 取得第 mid 個節點
            2. 觀察此題List特性 -> 分2半, 交叉接 -> (1)後半倒序, 前半數量 >= 後半 
            3. 怎麼分? -> 找中點切 -> 沒index、總數 -> 用快慢two pointers找 -> 最後slow的位置
*/

// class Solution {
// public:
//     // // Definition for singly-linked list.
//     // struct ListNode {
//     //     int val;
//     //     ListNode *next;

//     //     ListNode() : val(0), next(nullptr) {}
//     //     ListNode(int x) : val(x), next(nullptr) {}
//     //     ListNode(int x, ListNode *next) : val(x), next(next) {}
//     // };

//     void reorderList(ListNode *head) {
//         // 1. Find the middle
//         ListNode* slow = head, * fast = head->next;
//         while (fast != nullptr && fast->next != nullptr) {
//             slow = slow->next; // 最後slow就是中點(前半段數量剛好=或多一個)
//             fast = fast->next->next;
//         }
//         // 2. Rverse the second half
//         ListNode* second = slow->next; // 不直接用fast -> 不確定是否最後一個 or null
//         slow->next = nullptr; // 斷開後半

//         ListNode* prev = nullptr; // 開始Reverse
//         while (second != nullptr) { // second half的head不能是nullptr -> while不能==
//             ListNode* tmp = second->next; // 改向前先記, 避免遺失 -> 創建新pointer tmp
//             second->next = prev;
//             prev = second; // 先移動prev, 才能更新second!!!
//             second = tmp;
//         }
//         second = prev; // !!!注意: 跳出while loop -> 代表second為nullptr -> second的head不能是nullptr!!!

//         // 3. Merge the two list
//         ListNode* first = head;
//         while (second != nullptr) {
//             ListNode* tmp1 = first->next;
//             ListNode* tmp2 = second->next;

//             first->next = second;
//             second->next = tmp1;
            
//             first = tmp1; // 為下一輪更新
//             second = tmp2;
//         }
//     }
// };


/*
    3️⃣ Recursion- 
        T:O(n) = {call n 層} * {每層固定工作量O(1)}
            雖然要「往下呼叫，再往上返回」，但它們的工作量是相加，不是相乘。即使算成約 2n，也仍然是 O(n)。
        S:O(n) -> Recursion需要暫存空間
            最深處時，上面表格的 n 層呼叫都還同時存在。
            每一層需要保存自己的參數、區域變數與返回位置，這些是固定大小的資料，佔 O(1)。
            所以：
            {最大額外空間} = {同時存在 n 層} * {每層固定空間} = O(n)
*/

class Solution {
public:
    // // Definition for singly-linked list.
    // struct ListNode {
    //     int val;
    //     ListNode *next;

    //     ListNode() : val(0), next(nullptr) {}
    //     ListNode(int x) : val(x), next(nullptr) {}
    //     ListNode(int x, ListNode *next) : val(x), next(next) {}
    // };

    void reorderList(ListNode* head) {
        if (head == nullptr) return;
        rec(head, head->next); // call func
    }

    ListNode* rec(ListNode* root, ListNode* cur) { // 寫一個recursion func
        if (cur == nullptr) {return root;} // 傳到底後, 第一個要回傳最左root

        ListNode* resRoot = rec(root, cur->next); // ⚠️若第參數傳root->next, 因root往右走一路都是head -> 導致原地沒前進

        if (resRoot == nullptr) {return nullptr;} // 上一行回傳-> 馬上處理
        /* nullptr 就像「接線已完成」的通知：剩下的呼叫仍要逐層返回，但全部跳過接線。
            以五個節點為例，呼叫依序是：rec(1,2) → rec(1,3) → rec(1,4) → rec(1,5) → rec(1,nullptr)
            往下時固定前端 root，讓 cur 往尾端走。
            返回時，resRoot 接住下一個待配對的前端節點；
            若為 nullptr，表示已完成。
        */

        // 尚未完成，才會走到這裡接線
        ListNode* tmp;
        if (resRoot == cur || resRoot->next == cur) {
            cur->next = nullptr; // ⚠️🔥不是root—>next = nullptr !!!(因為偶數時root->next = cur 本來就有且正確, 且不會再進else判斷處理 -> 只要補最後的nullptr)
            return nullptr; // ⚠️🔥到中間時 -> return nullptr 代表「完成」！結束接線
        } else {
            tmp = resRoot->next; // 改ptr前先暫存
            resRoot->next = cur;
            cur->next = tmp;
            resRoot = tmp; // 可省略, 後面直接return tmp
        }
        return resRoot; 
    }
};



// int main() {

//     using ListNode = Solution::ListNode;

//     int a1, b1, c1, d1;
//     cout << "Enter values for nodes a, b, c, d: "; 
//     if (!(cin >> a1 >> b1 >> c1 >> d1)) {
//         cout << "Invalid input. Please enter four integers." << endl;
//         return 1; // Exit with error code
//     }

//     ListNode a(a1);
//     ListNode b(b1);
//     ListNode c(c1);
//     ListNode d(d1);

//     a.next = &b;
//     b.next = &c;
//     c.next = &d;
//     d.next = nullptr;

//     cout << "Before reorder: ";
//     ListNode* temp = &a;
//     while (temp != nullptr) {
//         cout << temp->val << " ";
//         temp = temp->next;
//     }
//     cout << endl;

//     Solution solution;
//     solution.reorderList(&a);

//     cout << "After reorder: ";
//     temp = &a;
//     while (temp != nullptr) {
//         cout << temp->val << " ";
//         temp = temp->next;
//     }
//     cout << endl;

//     return 0;
// }