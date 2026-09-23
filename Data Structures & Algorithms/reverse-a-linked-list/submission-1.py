class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reverseList(self, head:Optional[ListNode]) -> Optional[ListNode]:
        if not head:    #如果沒有head，直接回傳None（沒頭開始反轉）
            return None

        newHead = head  #如果有head，就先存進變數newHead裡
        if head.next:   #如果有下一個
            newHead = self.reverseList(head.next)   #呼叫函式，遞迴至最後，存取回傳值
            head.next.next = head   #下下一個指向自己，為反轉
        head.next = None    #

        return newHead      #每一層回溯都會回傳一樣的newhead = reverseList(head.next)

