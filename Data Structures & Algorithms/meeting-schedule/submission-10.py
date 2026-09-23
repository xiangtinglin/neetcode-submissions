"""
# 步驟:
1.排序: start time
2.比較: pre.end & cur.start
3.條件(False): pre.end > cur.start
————
# 工具:
Definition of Interval:
class Interval(object):
    def __init__(self, start, end):
        self.start = start
        self.end = end
"""
# class Interval(object):
#     def __init__(self, start, end):
#         self.start = start
#         self.end = end

class Solution:
    def canAttendMeetings(self, intervals:List[interval]) -> bool:
        intervals.sort(key=lambda x:x.start)
        for i in range(1, len(intervals)):  # ⚠️不要是負數: len(intervals) - 1 = 0 - 1（錯誤）
            if intervals[i - 1].end > intervals[i].start:
                return False
        return True

        