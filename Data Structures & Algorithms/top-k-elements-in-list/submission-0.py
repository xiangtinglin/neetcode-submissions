# Given: an integer array nums and an integer k
# return: the k most frequent elements within the array.
# thoughts: hash map + count {key = num : value = count}
# Complexity: aim for O(n) time and O(n) space (where n is the size of the input array).
# sol: 

'''
EX: nums = [1, 1, 1, 2, 2, 3] , k = 2
'''

# from typing import List
# from collections import Counter
# import heapq

class Solution:
    def topKFrequent(self, nums: List[int], k: int) -> List[int]:
        '''
        Sol 1: 極致Pythonic!!!（Tools）
        '''
        # return [num for num, freq in Counter(nums).most_common(k)]
        '''
        Sol 2: 實作Sorting
        '''
        # count = {}
        # for num in nums:
        #     count[num] = count.get(num, 0) + 1
        # arr = []
        # for num, freq in count.items():
        #     arr.append([freq, num])
        # arr.sort() # ascending

        # res = []
        # for _ in range(k):
        #     res.append(arr.pop()[1])
        # return res

        '''
        Sol 3: Min-Heap(前k大)
            Python 的 heapq 預設是 min-heap, heap = [(frequency, num)]
            heap 的底層是用 array 表示二元樹。(排序: 有沒有比它的 parent 小。)
            # 索引關係是：
                parent index = (i - 1) // 2
                left child = 2 * i + 1
                right child = 2 * i + 2
        '''
        # count = Counter(nums)
        # heap = []
        # for num, freq in count.items():
        #     heapq.heappush(heap, (freq, num))
        #     if len(heap) > k:
        #         heapq.heappop(heap)

        # res = []
        # for _ in range(k):
        #     res.append(heapq.heappop(heap)[1])
        
        # return res

        '''
        Sol 4: Bucket Sort
        '''
        count = Counter(nums)
        bucket_freq = [[] for _ in range(len(nums) + 1)]
        res = []
        for num, freq in count.items():
            bucket_freq[freq].append(num)
        for i in range(len(bucket_freq)-1 , 0, -1):
            for num in bucket_freq[i]:
                res.append(num)
                if len(res) == k:
                    return res

# def main():
#     sol = Solution()
#     while True:
#         try:
#             input_string = input("請輸入一串List(空格隔開): ")
#             k = int(input("請輸入k: "))
#             nums = []
#             for num in input_string.strip().split():
#                 nums.append(int(num))
#             print(sol.topKFrequent(nums, k))

#         except KeyboardInterrupt:
#             print("退出程式\n")
#             break
#         except Exception as e:
#             print(f"錯誤原因: {e}, 請重新輸入")
#             continue

# if __name__ == '__main__':
#     main()