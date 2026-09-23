// g++ -std=c++17 -Wall -Wextra -g3 /Users/xiang13air/Program/Leetcode/Test.cpp -o /Users/xiang13air/Program/Leetcode/output/Test

// # Given: an integer array nums and an integer k
// # return: the k most frequent elements within the array.
// # thoughts: hash map + count {key = num : value = count}
// # Complexity: aim for O(n) time and O(n) space (where n is the size of the input array).
// '''
// EX: nums = [1, 1, 1, 2, 2, 3] , k = 2
// Sol 1: 極致Pythonic!!!（Tools）
// Sol 2: 實作Sorting
// Sol 3: Min-Heap(前k大)— 🔥C++預設是max-heap!!!
// Sol 4: Bucket Sort
// '''

// # include <iostream>
// # include <vector>
// # include <unordered_map>
// # include <queue>
// # include <algorithm>
// using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // '''
        // Sol 2: 實作Sorting
        // '''
        // unordered_map<int, int> count; // 先計數
        // for (int& num : nums) {
        //     count[num] ++;
        // }
        // vector<pair<int, int>>arr; // num跟freq換位
        // for (const auto& p : count) {      
        //     arr.push_back({p.second, p.first});      
        // }
        // sort(arr.rbegin(), arr.rend()); // 再排序
        // vector<int> res;
        // for (int i = 0; i < k; i++) {
        //     res.push_back(arr[i].second); // ⚠️這時second是num，不是freq!
        // }
        // return res;
        
        // '''
        // Sol 3: Min-Heap(前k大)— 🔥C++預設是max-heap!!!
        // '''
        // unordered_map<int, int> count;
        // for (const auto& num : nums) {
        //     count[num]++;
        // }
        // priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;
        // for (const auto& p : count) {
        //     heap.push({p.second, p.first}); // ⚠️heap.push()沒有_back()!
        //     while (heap.size() > k) {
        //         heap.pop();
        //     }
        // }
        // vector<int> res;
        // while (!heap.empty()) {
        //     res.push_back(heap.top().second);
        //     heap.pop();
        // }
        // return res;

        // Sol 4️⃣: Bucket Sort
        unordered_map<int, int> count;
        for (int num : nums) {
            count[num]++;
        }
        vector<vector<int>> bucket_freq(nums.size() + 1);
        for (const auto& p : count) {
            bucket_freq[p.second].push_back(p.first);
        }
        vector<int> res;
        for (int i = bucket_freq.size() -1; i > 0; --i) {
            for (int num : bucket_freq[i]) {
                res.push_back(num);
                if (res.size() == size_t(k)) {
                    return res;
                }
            }
        }
        return res;
    }
};

// int main()
// {
//     vector<int> nums = {1, 1, 1, 2, 2, 3};
//     int k = 2;

//     Solution sol;
//     vector<int> result = sol.topKFrequent(nums, k);

//     cout << "[";
//     for (int num : result) {
//         cout << num;
//         if (num != result.back()) {
//             cout << ", ";
//         }
//     }
//     cout << "]" << endl;


//     return 0;
// };