// #include <iostream>
// #include <vector>
// #include <stack>
// #include <string>

// using namespace std;

/*
❓
1. given: an array of strings tokens
2. epresents: an arithmetic expression in a Reverse Polish Notation.
3. Return: an integer
⚠️ 這題的核心不是複雜計算，而是要看出：
1.「遇到數字先存起來；遇到運算子，就取出最近的兩個數字計算。」
2. 這種「後放進去的數字要先拿出來」的行為，正適用 Stack(堆疊)。
📖 Reverse Polish Notation:
1. 簡稱 RPN，中文常稱「逆波蘭表示法」或「後序表示法」
2. 最大的優點是不用括號，也不必另外判斷運算優先順序(本身排序已經決定)
*/


// /*
// 1️⃣ Brute Force- T:O(n^2); S:O(n)
// */
// class Solution {
// public:
//     int evalRPN(vector<string>& tokens) {
//         while (tokens.size() > 1) { // 用原本容器, 不另外開
//             for (int i = 0; i < static_cast<int>(tokens.size()); i++) {
//                 if  (tokens[i] == "+"
//                     || tokens[i] == "-"
//                     || tokens[i] == "*"
//                     || tokens[i] == "/")
//                 // 遇到operator就開始計算
//                 {
//                     int b = stoi(tokens[i - 1]);
//                     int a = stoi(tokens[i - 2]);
//                     int tmpRes = 0;
                    
//                     if (tokens[i] == "+") tmpRes = a + b;
//                     else if (tokens[i] == "-") tmpRes = a-b;
//                     else if (tokens[i] == "*") tmpRes = a*b;
//                     else if (tokens[i] == "/") tmpRes = a/b;

//                     // 用覆蓋 & erase, 不用insert
//                     tokens[i -2] = to_string(tmpRes);
//                     tokens.erase(tokens.begin() + i - 1, tokens.begin() + i + 1);
//                     // ⚠️ break必加‼️ (修改了 tokens 的內容&長度後，原本的 index i必須刷新 = 0)
//                     break;
//                 }
//             }
//         }
//         return stoi(tokens[0]);
//     }
// };



// /*
// 2️⃣ Doubly Linked List- T:O(n); S:O(n)
//     #思路: vector 中間刪除很慢→ 想找能 O(1) 刪除節點的資料結構
//         → Linked List
//         → 又需要往前取得兩個運算元→ Doubly Linked List
//     #結構:
//         before ⇄ left ⇄ right ⇄ operator ⇄ after
//                             ↓        cur
//         before ⇄    result               ⇄ after
// */

// // (1) 先自定義資料容器&型態class（DoublyLinkedList是自定義名稱, 非內建）
// class DoublyLinkedList {
// public:
//     string val;
//     DoublyLinkedList* next;
//     DoublyLinkedList* prev;
    
//     DoublyLinkedList(string initVal, DoublyLinkedList* initNext = nullptr, DoublyLinkedList* initPrev = nullptr): val(initVal), next(initNext), prev(initPrev) {} // inintializer取代{}內的this->
// };

// // (2) 建立list & function
// class Solution {
// public:
//     int evalRPN(vector<string>& tokens) {
//         // 先建立LinkedList, 從head開始
//         DoublyLinkedList* head = new DoublyLinkedList(tokens[0]);
//         DoublyLinkedList* initCurr = head;

//         for (int i = 1; i < static_cast<int>(tokens.size()); i++) {
//             initCurr->next = new DoublyLinkedList(tokens[i], nullptr, initCurr);
//             initCurr = initCurr->next;
//         }
//         //再來處理function
//         DoublyLinkedList* curr = head;
//         int ans = 0;
//         while (curr != nullptr) {
//             if (curr->val == "+" ||
//                 curr->val == "-" ||
//                 curr->val == "*" ||
//                 curr->val == "/") 
//                 {
//                     int l = stoi(curr->prev->prev->val);
//                     int r = stoi(curr->prev->val);
//                     int tmpAns = 0;
//                     if (curr->val == "+") tmpAns = l + r;
//                     else if (curr->val == "-") tmpAns = l - r;
//                     else if (curr->val == "*") tmpAns = l * r;
//                     else if (curr->val == "/") tmpAns = l / r;

//                     curr->val = to_string(tmpAns);
//                     ans = stoi(curr->val);
//                     curr->prev = curr->prev->prev->prev;
//                     if (curr->prev != nullptr) curr->prev->next = curr;
//                 }
//             curr = curr->next;
//         }
//         return ans;
//     }
// };


// /*
// 3️⃣Recursion- T:O(n); S:O(n)
//   ex: 2 1 + 3 *
//         *
//        / \
//       +   3
//      / \
//     2   1
// */
// class Solution {
// public:
//     // (1)先處理recursion設計(右到左), 包成函式方便call
//     int dfs(vector<string>& dfsTokens) {
//         string token = dfsTokens.back();
//         dfsTokens.pop_back();

//         if (token != "+" && token != "-" && 
//             token != "*" && token != "/") 
//             {
//                 return stoi(token);
//             }
//         int right = dfs(dfsTokens);
//         int left = dfs(dfsTokens);

//         if (token == "+") return left + right;
//         else if (token == "-") return left - right;
//         else if (token == "*") return left * right;
//         else if (token == "/") return left / right; 
//         // 🔥⚠️最後要回傳數值! 用“else” or “return 0;” or 報錯
//         throw invalid_argument("Invalid operator");
//     }
//     // (2) Call遞迴
//     int evalRPN(vector<string>& tokens) {
//         return dfs(tokens);
//     }
// };

/*
4️⃣ 🥇Stack(另外開容器處理, 原tokens都不更動)- T:O(n); S:O(n)
   #規則:
    數字    → push
    operator → pop 兩次、計算、push result
   #最佳解原因:題目的運算行為和 Stack 操作對應。
*/
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int>tmpStack; // ⚠️type: int
        for (const string& c : tokens) {
            if (c == "+") {
                int b = tmpStack.top(); tmpStack.pop();
                int a = tmpStack.top(); tmpStack.pop();
                tmpStack.push(a + b);
            } else if (c == "-") {
                int b = tmpStack.top(); tmpStack.pop();
                int a = tmpStack.top(); tmpStack.pop();
                tmpStack.push(a - b);
            } else if (c == "*") {
                int b = tmpStack.top(); tmpStack.pop();
                int a = tmpStack.top(); tmpStack.pop();
                tmpStack.push(a * b);
            } else if (c == "/") {
                int b = tmpStack.top(); tmpStack.pop();
                int a = tmpStack.top(); tmpStack.pop();
                tmpStack.push(a / b);
            } else {
                tmpStack.push(stoi(c));
            }
        }
        return tmpStack.top();
    }
};

// int main()
// {
//     vector<string> nums = {"3", "1", "+", "4", "*"};

//     Solution sol;
//     int result = sol.evalRPN(nums);
//     cout << "Result: " << result << endl;

//     return 0;
// };