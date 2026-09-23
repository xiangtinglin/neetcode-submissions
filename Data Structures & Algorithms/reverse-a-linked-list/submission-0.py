class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = None

class Solution:
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:  #函式中給定一個head，會回傳Linekd List反轉後的head
        prev, curr = None, head     #初始化（head是參數代入，指原本的head）

        while curr:           #終止條件——ListNode走完
            tmp = curr.next   #要逆轉第一個指標時，為避免curr.next位址遺失，先用tmp紀錄
            curr.next = prev   #curr.next指向prev
            prev = curr        #往下移動
            curr = tmp         
        return prev         #return反轉後的head

