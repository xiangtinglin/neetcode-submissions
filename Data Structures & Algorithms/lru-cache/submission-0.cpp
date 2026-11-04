/*
Ctrl + Shift + B：只編譯
clang++ .\Test.cpp -std=c++17 -g -Wall -Wextra -o .\Test.exe
.\Test.exe

*/

// #include <iostream>
// #include <unordered_map>
// #include <list>

// using namespace std;


/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

/*
    # Requirements: Design a data structure
            (follows the constraints of a Least Recently Used (LRU) cache. )
    # Implement:
        1.LRUCache(int capacity): Initialize the LRU cache with positive size capacity.
        2.int get(int key): Return the value of the key if the key exists, otherwise return -1.
        3.void put(int key, int value):
            (1)if the key exists: Update the value of the key.
            (2)Otherwise, add the key-value pair to the cache.
            (3)If the number of keys exceeds the capacity from this operation:
                -> evict the least recently used key.
    # must: 
        1.time complexity: The functions get and put must each run in O(1) average.

    # thoughts:
        1.第一步應該是把題目翻譯成「我要支援哪些操作」，再逐一替操作找資料結構。
        2.先忽略 \(O(1)\)，該怎麼做?
            (1)有一張清單，左邊最久沒用、右邊最近使用： LRU left(dummy) ⇄ ... ⇄ MRU right(dummy)
            (2)operation: 
                get(key): 找到 & 移到最右 ->> 找到key, 取得val, 移到最右(MRU)
                put(key, value): 放到最右邊 ->> 
                超過 capacity: 移除最左

*/


/*
 一、 Brute Force- 
        T:O(n) for each put() and get() operation.
        S:O(n)
        
        # thoughts:
            We store all (key, value) pairs in a list.
            To follow LRU (Least Recently Used) behavior
*/

// class LRUCache {
//     // 1-1.initial- vector, cap
// private:
//     vector<pair<int, int>> cache;
//     int capacity; // 宣告成員變數, 這個作用領, 所有class內都能用
// public:
//     // 1-2.initial- 物件
//     LRUCache(int capacity) {
//         this->capacity = capacity; // 因為右邊傳入參數命名跟宣告的成員變數同, 所以要用this->
//     }
//     // 2-1. fuc get
//     int get(int key) {
//         // 1.for loop through the vector to find the key
//         for (int i = 0; i < cache.size(); i++) {
//             // if found
//             if (cache[i].first == key) {
//                 pair<int, int> tmp = cache[i]; // tmp store(保存value, 因為參數沒有傳)
//                 cache.erase(cache.begin() + i); // !!!vector用.erase(指定位置), 不能放物件(cache[i])!
//                 cache.push_back(tmp);
//                 return tmp.second;
//             }
//         }
//         // 2.not found(注意return位置! outside the for loop)
//         return -1;
//     }
//     // 2-2. fuc put
//     void put(int key, int value) {
//         // 1.For loop to check wether [the key] is already in cache
//         for (int i = 0; i < cache.size(); i++) {
//             // (1)if found
//             if (cache[i].first == key) {
//                 cache.erase(cache.begin() + i); // 可直接erase免tmp store -> 因為參數key, value都有傳
//                 cache.push_back({key, value});
//                 return; // 原本void不需return!! 但此必須直接結束, 否則繼續往下會再次push!!!
//             }
//         }
//             // (2)not found
//         cache.push_back({key, value});

//         // 2.Check the capacity
//         while (cache.size() > capacity) {
//             cache.erase(cache.begin());
//         }
//         return; // 3.不用return
//     }
// };



/*
 二、Hash Map + Doubly Linked List
    T:O(1) for each put() and get() operation.
    S:O(n)

    # thoughts:
        1.對暴力法逐行做複雜度分析，找出究竟是哪個操作拖慢速度。 ->> vector (搜尋/刪除／移動任意位置太慢。)
        2.vector搜尋太慢 ->> unordered_map
        3.hash map能 key 對應 value, 但看不出來LRU/MRU關係資訊 
            ->> 若要排序, 跟vector一樣問題(刪除後, 後面元素搬移慢) ->> 用linked list
            ->> map的val改成ptr指向node, node內再存資訊(key, val, next, prev)
        4.什麼資料結構能快速移除已知位置？ ->> linked list !!!(只需要修改連線O(1))
        5.不能只用單向鏈結串列? ->> 不然還是要重頭開始O(n) ->> double linked list !!!
                ↓
        Ans: Hash Map 找位置(key, ptr) + node(key, val, next, prev) + 雙向鏈結串列維護順序
                (left ⇄ Node(key=2,val=2) ⇄ Node(key=1,val=1) ⇄ right)
                            LRU                    MRU
*/

// class LRUCache { // 這題不是要完成「一個函式」，而是要設計一個可以被持續操作的物件，所以 LeetCode 指定的類別名稱不是Solution
        // 1.create & initial- Node
//     struct Node { //struct預設內部public, 但仍在class裡 = private, 但此題不需要public, 因為: Node 只是 LRUCache 的內部實作細節。外部用不到new Node(), s只需要：LRUCache cache(2); cache.put(1, 1); cache.get(1);
//         int k;
//         int v;
//         Node* next;
//         Node* prev;

//         Node(int key, int value) : k(key), v(value), next(nullptr), prev(nullptr) {} // 建立Node時可能只有傳入k, v(ptr先初始化預設nullptr, 之後才改)
//     };
// private:
//     // 1-1.create & initial(inner satuff, func)- hash map, cap, dummy left/right
//     unordered_map<int, Node*> cache;
//     int cap;
//     Node* left; // 宣告為成員變數，讓 LRUCache 的各成員函式共用
//     Node* right;

//     // 1-2.create & initial(func)- Node: remove, insert(跟hashMap cache無關)
//     void remove(Node* node) { // 只動List
//         Node* p = node->prev;
//         Node* n = node->next;
//         p->next = node->next;
//         n->prev = node->prev;

//         node->prev = nullptr, node->next = nullptr; //防呆
//     }

//     void insert(Node* node) { // 只動List
//         Node* p = right->prev;

//         p->next = node;
//         node->prev = p;
//         node->next = right;
//         right->prev = node;
//     }

// public:
//     LRUCache(int capacity) {
//         cap = capacity;
//         left = new Node(0, 0);
//         right = new Node(0, 0);
//         left->next = right; // 記得初始基礎link
//         right->prev = left;
//     }
    
//     int get(int key) {
//         if (cache.find(key) != cache.end()) { // !!!絕對不能寫if (cache[key]), 若不存在會自動新增 & value給nullptr
//             Node* tmp = cache[key];
//             remove(tmp); // 交給helper處理
//             insert(tmp);
//             return tmp->v; // get()不用管hashMap cache
//         }
//         return -1;
//     }

//     void put(int key, int value) {
//         if (cache.find(key) != cache.end()) {
//             Node* node = cache[key];
//             node->v = value; // 先update value
//             remove(node);
//             insert(node);
//             return;
//         }
//         // not found(先new & add)
//         Node* newNode = new Node(key, value);
//         cache[key] = newNode;
//         insert(newNode);
//         // check cap
//         if (cache.size() > cap) {
//             Node* target = left->next;
//             cache.erase(target->k);
//             remove(target);
//             delete target;
//         }
//     }
// };



/*
 二-2、Built-In Data Structure
    T:O(1) for each put() and get() operation.
    S:O(n)

    # thoughts:
        不用自己寫struct Node {}, remove(), insert(), 維護doubleLinkedList的next/prev指向
        ->> 用內建 list<int> 資料結構取代 + 保留unordered_map查表概念
            unordered_map<
                int,                              // key
                pair<
                    int,                          // value
                    list<int>::iterator           // 在 order 的位置
                >
            > cache;

            list<int> order; // 只放key當對照依據, 呈現list前後關係
*/

class LRUCache {
private:
    unordered_map<int, pair<int, list<int>::iterator>> cache; // {key, (value, iterator)}
    list<int> order; // 只存int key
    int cap;

public:
    LRUCache(int capability) : cap(capability) {}

    int get(int key) {
        if (cache.find(key) != cache.end()) { // 也可以用order.find(), 但是: 1.搜尋時間O(n) 2.find方法不同 ->> std::find(order.begin(), order.end(), key); std::find 不屬於 order，它是一個獨立的通用函式。
            order.erase(cache[key].second); // 先改位置
            order.push_back(key); // push_back可指定最右的位置
            cache[key].second = --order.end(); // order更新位置 ->> 記得更新map資訊(不能寫order.end()--)
            return cache[key].first;
        }
        return -1;
    }

    void put(int key, int value) {
        // not found
        if (cache.find(key) == cache.end()) {
            order.push_back(key);
            cache[key].first = value;
            cache[key].second = --order.end();
        } else { // found
            order.erase(cache[key].second);
            order.push_back(key);
            cache[key] = {value, --order.end()}; // update
        }
        //check cap!
        while (cache.size() > cap) {
            int targetKey = order.front(); // tmp store
            order.pop_front();
            cache.erase(targetKey); // map.erase可以直接傳key, 不用傳位置
        }
    }

    void printOrder() const {
        cout << "LRU -> MRU: ";

        for (int key : order) {
            cout << key << " ";
        }

        cout << '\n';
    }
};


// int main() {
//     LRUCache* obj = new LRUCache(2);
//     obj->put(1, 1);
//     obj->put(2, 2);
//     cout << obj->get(1) << endl; // returns 1
//     obj->put(3, 3);              // evicts key 2
//     cout << obj->get(2) << endl; // returns -1 (not found)
//     obj->put(4, 4);              // evicts key 1
//     cout << obj->get(1) << endl; // returns -1 (not found)
//     cout << obj->get(3) << endl; // returns 3
//     cout << obj->get(4) << endl; // returns 4

//     obj->printOrder(); // Output: LRU -> MRU: 3 4
//     delete obj;
//     return 0;
// }