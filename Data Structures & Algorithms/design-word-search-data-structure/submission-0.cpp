// clang++ .\Test.cpp -std=c++17 -o Test.exe
// .\Test.exe

// #include <iostream>

// using namespace std;


/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
 

/*
 [題目理解]
    1.重點: 只取英文字元, 處理符號"." & ".."
        ->> word in search consist of '.'(at most 2 dots) or lowercase English letters.
    2.規則:
        (1)addWord: 無特殊情況
            限制: word in addWord consists of lowercase English letters.
        (2)search: 
            一般字母必須完全相同。
            . 可以代表任意一個小寫字母。
            . 只能代表「一個」字母，不能代表零個或多個字母。
            轉換後, 必須符合完整單字，只有 prefix 不算。(長度)
*/


/*
 一、【Brute Force】
    T:O(m*n) for search()
    S:O(m*n) for addWord(); O(1) for search()
    (Where m is the number of words added and n is the length of the string.)
    
    # thoughts: 把所有addWord加入同一個vector<string>, for loop(nested) to check.
*/

// class WordDictionary {
// public:
//     // 此無須struct TrieNode !

//     vector<string> wordV; // 宣告在公作用域

//     WordDictionary() { // 無須做什麼
//     }

//     void addWord(string word) { // 都是正常lowercase letter
//         wordV.push_back(word);
//     }
    
//     bool search(string word) {
//         bool match;
//         // 1.nested for loop: 
//         for (const string& w : wordV) {
//             // (1)check length first! (長度符合才往下, otherwise: continue)
//             if (word.size() != w.size()) {continue;}
//             // (假設match = ture)
//             match = true;
//             // (2)for loop (char by char) to check: 
//             for (int i = 0; i < word.size(); i++) {
//                 // (i)判斷條件(遇到"." || 一樣字元 ->> continue; 非"." && 不符合字元 ->> break(當前word不用再檢查)
//                 if (word[i] != '.' && word[i] != w[i]) {
//                     match = false;
//                     break; // 一有不符合的 cahr ->> 改match & break(剩下也一定不符合, 直接下一個w)
//                 }
//             }
//             // (3)out of loop(inner): 
//             if (match) {return true;} // 到此, 都沒被改成 false ->> 代表當前match 為 true (每word都檢查, 當下若match就return(避免後續多餘檢查 or 被 false覆蓋!!!))
//         }
//         // 2.out of loop(outer): 全檢查過, 都沒match ->> false
//         return false; // 必是 false, 否則前面早已 return ture;
//     }
// };


/*
 二、[DFS] & 26 alphabets
    T:O()
    S:O()

    # thoughts:
        1. 時間很難省, 省空間: 暴力解用額外的vector<string>
            ->> 取代存實體的容器: 改成char 字元定位 & 指標
            ->> 需要自己創建、模擬 node & 指向
*/

class WordDictionary {
public:
    // 1.initial & 創node
    struct TrieNode {
        TrieNode* children[26] {}; // attribute 宣告 & instance化簡, 寫在一起!
        bool endOfWord = false;
    };

    // 2.initial
    TrieNode* dummyNode;
    WordDictionary() {
        dummyNode = new TrieNode();
    }

    void addWord(string word) {
        TrieNode* cur = dummyNode;
        for (char c : word) {
            int index = (c - 'a');
            if (cur->children[index] == nullptr) {
                cur->children[index] = new TrieNode();
            }
            cur = cur->children[index];
        }
        cur->endOfWord = true; // label 最後一個
    }

    bool search(string word) {
        // 設計一個helper func
        return dfs(word, 0, dummyNode);
    }

    // 自己寫helper- 設計需要紀錄哪些傳入參數
    bool dfs(string w, int j, TrieNode* node) {
        TrieNode* cur = node; // 不能寫 TrieNode* cur = dummyNode;
        // 一個一個node來
        for (int i = j; i < (int)w.size(); i++) { // 後面要遞迴, 需要傳遞減的substring ->> 需要index定位range
            char c = w[i];
            if (c != '.') { // 先判斷 char 種類: 有明確 char ->> 有確定目標 & child[index], 只要檢查唯一可能 ->> 一個沒對上存在, 直接不符合
                if (cur->children[c - 'a'] == nullptr) {
                    return false;
                } else {
                    cur = cur->children[c - 'a']; // 有對上就繼續
                }
            } else { // 處理: c == '.' ->> 要檢查當前層, 每個往下展開 所有存在的dfs可能 ->> 要recursion !
                for (TrieNode* child : cur->children) {
                    if (child != nullptr && dfs(w, i + 1, child)) { // dfs到底, 都通過的條件
                        return true;
                    }
                }
                // 若都沒return true
                return false;
            }
        }
        return cur->endOfWord; // 若 c != '.' 且一直符合, 就會到這 ->> 最後還需要判斷: bool endOfWord!!!
    }
};


// int main() {
//     WordDictionary* obj = new WordDictionary();

//     string word1 = "bad";
//     string word2 = "dad";
//     string word3 = "mad";
//     cout << "Adding words: " << word1 << ", " << word2 << ", " << word3 << endl;
//     obj->addWord(word1);
//     obj->addWord(word2);
//     obj->addWord(word3);

//     while (true) {
//         string searchWord;
//         cout << "Enter a word to search (or type 'exit' to quit): ";
//         cin >> searchWord;
//         if (searchWord == "exit") {
//             break;
//         }
//         bool found = obj->search(searchWord);
//         cout << boolalpha << found << endl;
//     }

//     delete obj; // Clean up memory
//     return 0;
// }