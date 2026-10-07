// clang++ -Wall -Wextra -Werror -std=c++17 -o Test_string Test_string.cpp

// #include <iostream>
// #include <vector>
// #include <unordered_map>

// using namespace std;


/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
 
/*
    # 核心: 
        1. 不需寫程式讀取 Input；要實作 TimeMap 類別，讓測試程式能呼叫 set() 和 get()
        2. 字典需保留同一個 key 在不同時間的值
    # 容器- Design a time-based key-value data structure:
        set input -> ["key", "value", int timeStamp]
        Data structure ->  {["key1": [(1, "bad"), (3, "sad")] ], ["key2": [(2, "sad"), (4, "happy")]], ...}
    # function:
        0. TimeMap()
            建立物件時，準備好儲存資料的容器
        1. void set(String key, String value, int timestamp)
        2. string get(String key, int timestamp)
            Return "" or 
                value(with timestamp_prev <= timestamp) -> 找<=中最新(largest timestamp_prev)
*/



/*
    1️⃣ Brute Force
        T: O(1) for set() and O(n) for get().
        S: O(m * n)
            Where n is the total number of unique timestamps associated with a key and m is the total number of keys.
        
        # Data struct: unordered_map<string, unordered_map<int, vector<string>>>
*/

// class TimeMap {
// private:
//     unordered_map<string, unordered_map<int, string>> records;
// public:
//     TimeMap() {}; // initialize! 放public -> 外部可建立物件。
//     // map宣告不能包在初始化中 -> 變成區域變數, 建構子執行結束，它就被銷毀
//     void set(string key, string value, int timestamp) {
//         records[key][timestamp] = value;
//     }

//     string get(string key, int timestamp) {
//         if (records.find(key) == records.end()) {return "";} // ⚠️型別同，才能比較!!! .find()跟.end() 都是iterator
        
//         int flag = -1; // 1 <= timestamp <= 107, 所以0也行
//         for (const auto& [time, val] : records[key]) {
//             if (time <= timestamp) {flag = max(flag, time);}
//         }
//         return flag == -1 ? "" : records[key][flag]; // 如果records[key][flag]是vecotr<string>, 就要.back()
//     }
// };


/*
    2️⃣ ✨Binary Search(搭配sorted map & .upper_bound())
        T: 
            set(): O(log n) or O(n) depending on the language 
                    C++實作 = 外層O(1) + 內層map O(log n) 
            get(): O(log n)
        S: O(m * n)
            Where 
                n: the total number of unique timestamps associated with a key
                m: total number of keys.
        # Data structure: unordered_map<string, map<int, string>>& records; C++ 的 map 通常用「平衡二元搜尋樹」儲存資料。插入時沿著樹往下找位置，走的層數約是 \(\log_2 n\)。

        # 🔥核心: 非手寫二分搜尋, 而是利用map本身。
            它使用 map::upper_bound()，讓有序的 map 找時間邊界。C++ 的 map 通常用平衡搜尋樹實作，這裡是樹上的 \(O(\log n)\) 查找，不是陣列上的二分搜尋。
*/

// class TimeMap {

// private:
//     unordered_map<string, map<int, string>> records;
// public:
//     TimeMap() {}

//     void set(string key, string value, int timestamp) {
//         records[key].insert({timestamp, value}); // insert() 保留原值，[] = value 覆蓋原值。
//     }

//     string get(string key, int timestamp) { // 利用map本身特性定位
//         auto pos = records[key].upper_bound(timestamp); 
//         /* map有序才能用bound.  用upper_bound找第一個 > 的元素, 可以直接往前取到正確值; 不用lower_bound, 因找第一個 >= 的元素 無法直接知道是哪種情況 */ 
//         return (pos == records[key].begin()) ? "" : prev(pos)->second; // pos == records[key].begin()表示空or無解(沒<=的)
//         /*
//         ⚠️iterator 用 -> ; pair用.second 
//         ⚠️map裡面實作元素是pair<const int, string>
//         */
//     }
// };


/*
    3️⃣ Binary Search(Array)
        (1)容器: 搭配Array, 不用Sorted map (2)實際2元搜尋寫法
        T: set(): O(1); get(): O(log n)
        S: O(m * n)
            Where 
                n: the total number of unique timestamps associated with a key
                m: total number of keys.
*/

class TimeMap {
private:
    unordered_map<string, vector<pair<int, string>>> records;
    // 題目的輸入保證讓 vector 有序，不是 vector 自動排序 -> 略過排序, 直接二元搜尋
public:
    TimeMap() {}

    void set(string key, string value, int timestamp) {
        records[key].push_back({timestamp, value}); // .push_back記得pair要用{}
    }

    string get(string key, int timestamp) {
        int n = records[key].size();
        int l = 0, r = n - 1;
        string res = ""; // 預設空字串

        while (l <= r) {
            int m = l + ((r - l) / 2);
            if (records[key][m].first <= timestamp) {
                res = records[key][m].second;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return res;
    }
};


// int main() {
//     TimeMap* obj = new TimeMap();

//     cout << "Ex:\n\t set:[[\"foo\", \"bar\", 1], [\"foo\", \"bar2\", 4], [\"foo\", \"bar3\", 7], [\"XXX\", \"Xbar4\", 8]]" << endl;
//     cout << "\t get:[[\"foo\", 5], [\"XXX\", 9]]" << endl;
//     cout << "\tOutput: should be \"bar2\" and \"Xbar4\"" << endl;

//     obj->set("foo", "bar", 1);
//     obj->set("foo", "bar2", 4);
//     obj->set("foo", "bar3", 7);
//     obj->set("XXX", "Xbar4", 8);
//     string param_2_1 = obj->get("foo", 5);
//     string param_2_2 = obj->get("XXX", 9);

//     cout << "\nResult: " << param_2_1 << " and " << param_2_2 << endl;

// }