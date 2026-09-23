# 1️⃣ Determine if a 9 x 9 Sudoku board is valid. -> T / F
# 2️⃣ “Only the filled cells need to be validated” -> not necessarily solvable
# 3️⃣ 解體核心: 
#  檢查3件事(每看到一個數字，例如 x，要確認它有沒有出現；若是.為空則跳過):
# （1）第 i 列出現過 x 嗎？
# （2）第 j 行出現過 x 嗎？
# （3）第 k 個 3x3 宮格出現過 x 嗎？
#   -> 只要任一地方出現過，代表「重複」，直接回傳 False。
#   -> row set + column set + box set
# 4️⃣ 特別點- 3x3 宮格編號方式:
#    box_index = (r // 3) * 3 + (c // 3)
#    因為 9 個小宮格可以編號成：
#    0 1 2
#    3 4 5
#    6 7 8

class Solution:
    # # 1️⃣ Brute Force -> T: O(3n²) / S: O(n) -> 同一格會被掃很多次
    # def isValidSudoku(self, board: List[List[str]]) -> bool:
    #     # (1)先檢查row
    #     for row in range(9):
    #         seen = set()
    #         for col in range(9):
    #             if board[row][col] == ".":
    #                 continue
    #             if board[row][col] in seen:
    #                 return False
    #             seen.add(board[row][col])
    #     # (2)再檢查col
    #     for col in range(9):
    #         seen = set()
    #         for row in range(9):
    #             if board[row][col] == ".":
    #                 continue
    #             if board[row][col] in seen:
    #                 return False
    #             seen.add(board[row][col])
    #     # (3)還要逐一檢查squares
    #     for square in range(9):
    #         seen = set()
    #         for i in range(3):  # 每個square是 3x3
    #             for j in range(3):
    #                 # 先處理row、col計算
    #                 row = (square // 3) * 3 + i
    #                 col = (square % 3) * 3 + j
    #                 if board[row][col] == ".":
    #                     continue
    #                 if board[row][col] in seen:
    #                     return False
    #                 seen.add(board[row][col])
    #     return True

    # # 2️⃣ One Pass(Hash Map/Hash Sets) -> T: O(n²) / S: O(n²) -> 一次檢查完row、col、box
    # #         Hash Map:
    # #             key   → row / col / square index
    # #             value → Hash Set of seen digits
    # def isValidSudoku(self, board: List[List[str]]) -> bool:
    #     # rows = defaultdict(set)
    #     # cols = defaultdict(set)
    #     # squares = defaultdict(set)

    #     # 用List不用dict的話
    #     rows = [set() for i in range(9)]
    #     cols = [set() for i in range(9)]
    #     squares = [set() for i in range(9)]

    #     for r in range(9):
    #         for c in range(9):
    #             val = board[r][c]

    #             if val == ".":
    #                 continue
    #             # if (val in rows[r]
    #             #     or val in cols[c] 
    #             #     or val in squares[(r // 3, c // 3)]):
    #             #     return False

    #             # List寫法
    #             box_index = (r // 3) * 3 + (c // 3)
    #             if (val in rows[r]
    #                 or val in cols[c] 
    #                 or val in squares[box_index]):
    #                 return False

    #             rows[r].add(val)
    #             cols[c].add(val)
    #             # squares[(r // 3, c // 3)].add(val)
    #             # List 寫法
    #             squares[box_index].add(val)
    #     return True

    # # 3️⃣ Bitmask -> T: O(n²) / S: O(n) -> 不用分開數字存set, 一個整數包含一整個set的資訊
    def isValidSudoku(self, board: List[List[str]]) -> bool:
        rows = [0] * 9
        cols = [0] * 9
        squares = [0] * 9

        for r in range(9):
            for c in range(9):
                val = board[r][c]
                if val == ".":
                    continue

                bit_pos = int(val) - 1
                mask = 1 << bit_pos
                box_index = (r // 3) * 3 + c // 3
                # 檢查是否重複
                if rows[r] & mask: # 只看那一位bit
                    return False
                if cols[c] & mask:
                    return False
                if squares[box_index] & mask:
                    return False
                
                rows[r] |= mask
                cols[c] |= mask
                squares[box_index] |= mask
        return True