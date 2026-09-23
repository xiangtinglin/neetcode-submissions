# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next

class Solution:
    def hasCycle(self, head: Optional[ListNode]) -> bool:
        rabbit, turtle = head, head  # Floyd Cycle Detection Algorithm(又稱龜兔賽跑算法)

        while rabbit and rabbit.next: #至少有2個node才討論是否有循環(1個也可以指給自己，但不符合題目情境)
            rabbit = rabbit.next.next
            turtle = turtle.next        #烏龜走1步，兔子走2步
            if rabbit == turtle:        #如果步伐不同的2者相遇——代表有cycle
                return True
        return False        #代表兔子先走到底了


        