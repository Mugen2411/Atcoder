#include <iostream>

int CountBit(int v)
{
    int cnt = 0;
    for (int i = 0; i < 16; ++i)
    {
        if (v & (1 << i))
        {
            ++cnt;
        }
    }
    return cnt;
}

int main()
{
    int N, M, K;
    int A[100] = {0};
    char R[100] = {0};
    std::cin >> N >> M >> K;
    for (int m = 0; m < M; ++m)
    {
        int C;
        std::cin >> C;
        for (int c = 0; c < C; ++c)
        {
            int a;
            std::cin >> a;
            A[m] |= 1 << (a - 1);
        }
        std::cin >> R[m];
    }
    size_t ans = 0;
    for (int i = 0; i < (1 << N); ++i)
    {
        bool isAns = true;
        for (int m = 0; m < M; ++m)
        {
            switch (R[m])
            {
            case 'o':
            {
                int e = A[m] & i;
                if (CountBit(e) < K)
                {
                    isAns = false;
                }
            }
            break;
            case 'x':
            {
                int e = A[m] & i;
                if (CountBit(e) >= K)
                {
                    isAns = false;
                }
            }
            break;
            default:
                break;
            }
            if (!isAns)
            {
                break;
            }
        }
        if (isAns)
        {
            ++ans;
        }
    }
    std::cout << ans;
    return 0;
}