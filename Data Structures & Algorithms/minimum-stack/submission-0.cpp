/*
1. Func:push, pop, top, and retrieving the minimum element 
2. O(1) time complexity for each function
⚠️: 
stack無法用index，要找最大/小，需要逐一 .top() -> .pop() -> .push()
*/

class MinStack {
/*
1️⃣ Brute force- T & S: O(n) for getMin() and O(1) for other operations
*/
// private:
//     stack<int> stk;
// public:
//     // nitializes
//     MinStack() {}
//     void push(int value) {
//         stk.push(value);
//     }

//     void pop() {
//         stk.pop();
//     }

//     int top() {
//         return stk.top();
//     }
    
//     // ⚠️stack操作!
//     int getMin() {
//         stack<int> tmp;
//         int res = stk.top();
//         while (stk.size()) {
//             res = min (stk.top(), res);
//             tmp.push(stk.top());
//             stk.pop();
//         }
//         while (tmp.size()) {
//             stk.push(tmp.top());
//             tmp.pop();
//         }

//         return res;
//     }

/*
2️⃣ 🏆 Two Stacks- 
T: O(1) for all operations
S: O(n)
*/
private:
    stack<int> stk;
    stack<int> minStk;
public:
    MinStack() {}
    void push(int value) {
        stk.push(value);
        int curMin = min(value, minStk.empty() ? value : minStk.top());
        minStk.push(curMin);
    }
    void pop() {
        stk.pop();
        minStk.pop();
    }
    int top() {
        return stk.top();
    }
    int getMin() {
        return minStk.top();
    }

// /*
// 3️⃣ One Stack-
// 利用差值正負判斷最小值是否改變: diff = val - 舊的 min
// */
// private:
//     stack<long long> diffStk;
//     long long min;
// public:
//     MinStack() {}
//     void push(int value) {
//         if (diffStk.empty()) {
//             // 先處理diff，若是-則更新min
//             diffStk.push(0);
//             min = value;
//         } else {
//             diffStk.push(value - min);
//             if (value < min) {min = value;}
//         }
//     }
//     void pop() {
//         if (diffStk.empty()) return;

//         long long diffTop = diffStk.top();
//         diffStk.pop();
//         if (diffTop < 0) min = min - diffTop;
//     }
//     int top() {
//         long long diffTop = diffStk.top();
//         return static_cast<int>(diffTop < 0 ? min : diffTop + min);
//     }
//     int getMin() {
//         return static_cast<int>(min);
//     }

};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */