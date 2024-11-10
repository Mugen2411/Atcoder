import copy

S = list(input())
T = list(input())

X = []

length = len(S)

while S != T:
    tmp = []
    for i in range(length):
        if S[i] != T[i]:
            tmp.append(S.copy())
            tmp[-1][i] = T[i]
    tmp.sort()
    X.append(tmp[0])
    S = tmp[0]

print(len(X))
for s in X:
    print("".join(s))