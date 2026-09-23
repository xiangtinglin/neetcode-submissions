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
        for i in range(0, len(intervals) - 1):
            if intervals[i].end > intervals[i + 1].start:
                return False
        return True

        