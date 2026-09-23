class Solution {
public:
    int maxProfit(vector<int>& prices) { //「&」是直接引用參考的意思，不用另外複製以節省空間
        int maxP = 0;
        int minBuy = prices[0];

        for (int& sell : prices) {     // 對 prices 容器中的每個元素進行遍歷，並將每個元素的參考賦值給 sell（冒號 : 將迴圈控制變數與容器連接起來，表示「遍歷……中的每個元素」）
            maxP = max(maxP, sell - minBuy);
            minBuy = min(minBuy, sell);
        }
        return maxP;
    }

};      // 在 C++ 中，定義class或結構體時，最後需要加上分號（;），這是語法規定。