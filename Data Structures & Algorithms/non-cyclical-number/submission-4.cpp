// Given: a positive integer "n"（replace it with the sum of the squares of its digits.）
// return: boolean （until the number equals 1, or it loops infinitely in a cycle）

// T / S: aim for O(logn) time and O(logn) space
// Solution: (1)Hash Set (2)Fast And Slow Pointers(Floyd's cycle detection)

class Solution {
public:
    // bool isHappy(int n) {
    //     unordered_set<int> seen;
    //     int temp = n;
    //     while (seen.find(temp) == seen.end()) {
    //         if (temp == 1) {
    //             return true;
    //         }
    //         seen.insert(temp);
    //         temp = sumOfSquares(temp);
    //     }
    //     return false;
    // }

    bool isHappy(int n) {
        int slow = n, fast = sumOfSquares(n);
        while (slow != fast) {
            if (slow == 1 || fast == 1) {
                return true;
            }
            slow = sumOfSquares(slow);
            fast = sumOfSquares(sumOfSquares(fast));
        }
        return fast == 1;
    }

public:
    int sumOfSquares(int x) {
        int res = 0;
        while (x > 0) {
            int digit = x % 10;
            digit *= digit;
            res += digit;
            x /= 10;
        }
        return res;
    }
};