# 関数定義スペース
def calc(a,b):
    return a[0]+b[0],a[1]+b[1]

def look(pos):
    return BOARD[pos[0]][pos[1]]

def dfs(pos,count=0,done=set()):
    if look(pos)=="#":
        return 0
    if count==K:
        return 1
    result=0
    for k in RLUD:
        new_pos=calc(pos,k)
        if new_pos not in done and look(new_pos)==".":
            done.add(new_pos)
            result+=dfs(new_pos,count+1,done)
            done.pop()
    return result


    
# 入力スペース ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Lit_to
H, W, K = map(int,input().split())
BOARD = [list(input()+"#") for i in range(H)]#文字列のリスト
BOARD.append(["#"]*(W+1))
RLUD=[(0,1),(0,-1),(-1,0),(1,0)]
# 処理スペース ================================================================================================Lit_to


result=0
for i in range(H):
    for j in range(W):
        done=set()
        done.add((i,j))
        result+=dfs((i,j),0,done)
print(result)
