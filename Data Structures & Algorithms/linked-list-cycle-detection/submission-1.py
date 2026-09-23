# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def hasCycle(self, head: Optional[ListNode]) -> bool:
        visited = set()  # 創建一個Hash Set供存放已走過的node(address)
        curr = head      

        while curr:
            if curr in visited:
                return True
            visited.add(curr)
            curr = curr.next
        return False


        