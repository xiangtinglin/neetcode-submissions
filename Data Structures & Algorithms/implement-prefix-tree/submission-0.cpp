/*
Ctrl + Shift + B：只編譯
clang++ .\Test.cpp -std=c++17 -g -Wall -Wextra -o .\Test.exe
.\Test.exe

*/

// #include <iostream>

// using namespace std;


/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
 

/*
 [題目理解]
    # thoughts:
        1.建構設計- 思考字母char跟指標如何運用、對照?
        2.非一般Binary Tree, Trie可能有多個children
*/


/*
 一、[Prefix Tree (Hash Map)]: Tree(children) & HashMap("char" : *)
    T:O(n) for each function call.
    S:O(t) 
    (where n is the length of word, t is the num of all tree nodes created.)
*/

// class Trie {
// public:
//     // 1.Initial TrieNode
//     struct TrieNode { // 不用instance 傳入任何參數, 也不用紀錄本身value(存在hash map的key : 直接對應指標)
//         unordered_map<char, TrieNode*> children;
//         bool endOfWord = false; // 標註, 用於 search 辨識, 預設: false
//     };

//     TrieNode* dummyRoot; // !!!記得在公區宣告 ->> 不同func才都可用
//     Trie() { // 初始化dummy root
//         dummyRoot = new TrieNode();
//     }
    
//     void insert(string word) {
//         TrieNode* cur = dummyRoot;
//         // 1.for loop: char by char
//         for (char c : word) {
//         // 2.check exist or not
//             if (cur->children.find(c) == cur->children.end()) {
//                 cur->children[c] = new TrieNode();
//             }
//             cur = cur->children[c];
//         }
//         // 3.out of loop: label endOfWord
//         cur->endOfWord = true;
//     }
    
//     bool search(string word) {
//         TrieNode* cur = dummyRoot;
//         // 1.for loop: char by char
//         for (char c : word) {
//         // 2.check exist or not(return false;)
//             if (cur->children.find(c) == cur->children.end()) {return false;}
//             cur = cur->children[c];
//         }
//         // 3.out of loop: check if endOfWord label of cur node is true
//         return cur->endOfWord;
//     }
    
//     bool startsWith(string prefix) {
//         TrieNode* cur = dummyRoot;
//         // 1.for loop: char by char
//         for (char c : prefix) {
//         // 2.check exist or not(return false;)
//             if (cur->children.find(c) == cur->children.end()) {return false;}
//             cur = cur->children[c];
//         }
//         // 3.out of loop: return ture;
//         return true;
//     }
// };



/*
 二、Prefix Tree (Array)
    T:O(n) for each function call.
    S:O(26t) = O(t) 
    (where n is the length of word, t is the num of all tree nodes created.)

    # thoughts:
        不用hash map, 改用每個node對應26個字母定位(宣告array, 連續26個 TrieNode*)
*/

class PrefixTree {
public:
    struct TrieNode {
        TrieNode* children[26] {}; // array 是連續空間. 初始化nullptr可用(1)constructor & for loop (2) {}
        bool endOfWord = false;
    };

    TrieNode* dummyRoot; // 公區宣告
    PrefixTree () {
        dummyRoot = new TrieNode();
    }

    void insert(string word) {
        TrieNode* cur = dummyRoot;
        for (char c : word) {
            int index = (c - 'a');
            if (cur->children[index] == nullptr) {
                cur->children[index] = new TrieNode();
            }
            cur = cur->children[index];
        }
        cur->endOfWord = true;
    }

    bool search(string word) {
        TrieNode* cur = dummyRoot;
        for (char c : word) {
            int index = (c - 'a');
            if (cur->children[index] == nullptr) {return false;}
            cur = cur->children[index];
        }
        return cur->endOfWord;
    }

    bool startsWith(string prefix) {
        TrieNode* cur = dummyRoot;
        for (char c : prefix) {
            int index = (c - 'a'); 
            if (cur->children[index] == nullptr) {return false;}
            cur = cur->children[index];
        }
        return true;
    }
};


// int main() {
//     Trie trie;

//     trie.insert("apple");

//     string input1;
//     cout << "input string 1: ";
//     cin >> input1;
//     trie.insert(input1);

//     cout << "input string 2: ";
//     string input2;
//     cin >> input2;
//     trie.insert(input2);

//     cout << "input string to search: ";
//     string searchInput;
//     cin >> searchInput;
//     cout << boolalpha << trie.search(searchInput) << endl;

//     cout << "input prefix string: ";
//     string prefixInput;
//     cin >> prefixInput;
//     cout << boolalpha << trie.startsWith(prefixInput) << endl;

//     return 0;
// }