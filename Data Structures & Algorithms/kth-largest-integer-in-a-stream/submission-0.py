'''
【 Min-Heap 】
1.including duplicates
2.not necessarily sorted
3.只求前k大，用minHeap
時間複雜度:__init__ — O(n log n) + add — O(log k)
空間複雜度: O(k)
'''
class KthLargest:
    def __init__(self, k:int, nums:List[int]):
        self.k = k
        self.minheap = nums             # 命名代表接下來要把list轉換成minheap
        heapq.heapify(self.minheap)     # ⚠️heapq.heapify() 只會建立minheap（若要maxheap需要另外處理）
        while len(self.minheap) > k:
            heapq.heappop(self.minheap)
        
    def add(self, val:int) -> int:
        heapq.heappush(self.minheap, val)
        while len(self.minheap) > self.k:
            heapq.heappop(self.minheap)     # pop out 最上面那個
        return self.minheap[0]              # 返回最小值，即第k大的數
