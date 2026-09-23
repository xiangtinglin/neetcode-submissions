# Definition for Linked list
class ListNode:
    def __init__(self, val=0, next=None):   # 給2個屬性資料
        self.val = val  # node的address裡存的值
        self.next = next

class Solution:
    def mergeTwoLists(self, list1:ListNode, list2:ListNode) -> ListNode:
        # 創建dummy node(主要目的:方便return排序後的head) 
        dummy = curr = ListNode()  #curr方便追蹤當前node

        while list1 and list2:     #處理不同情況——當2者都有node時，開始比大小
            if list1.val <= list2.val:  #list比較小，接在curr後
                curr.next = list1       
                list1 = list1.next      #更新list1剩下未排的第一個address
            else:
                curr.next = list2
                list2 = list2.next
            curr = curr.next            #不管誰先排，都更新curr
        #跳出迴圈——只有其中一個list有node時
        curr.next = list1 or list2  
        #都沒node可排時
        return dummy.next   #把dummy當作定海神針(dummy.next會得到None/Head)