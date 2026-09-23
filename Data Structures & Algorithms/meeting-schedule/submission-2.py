from typing import List
# Definition of Interval:
class Interval(object):
    def __init__(self, start, end):
        self.start = start
        self.end = end

class Solution:
    def canAttendMeetings(self, intervals: List[Interval]) -> bool:
        intervals.sort(key=lambda x:x.start)
        for i in range(len(intervals)-1):
            if intervals[i].end > intervals[i + 1].start:
                return False
        return True
'''
if __name__ == '__main__':
    sol = Solution()
    n = int( input("input meeting set numbers:") )
    intervals = []
    for i in range(1, n + 1):

        while True:
            try:
                start, end = map( int, input(f"輸入第{i}組會議時間start, end.(例如:3 5):").split() )
                intervals.append( Interval(start, end) )
                break
            except:
                print("Input Error!")
    print(sol.canAttendMeetings(intervals))
'''