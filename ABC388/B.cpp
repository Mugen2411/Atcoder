#include <iostream>
#include <vector>

int main()
{
    int N, D;
    std::cin >> N >> D;
    struct SNAKE
    {
        int T;
        int L;
        int W;
    };
    std::vector<SNAKE> S(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> S[i].T >> S[i].L;
        S[i].W = S[i].T * S[i].L;
    }
    for (int i = 0; i < D; ++i)
    {
        int ans = 0;
        for (int j = 0; j < N; ++j)
        {
            S[j].W += S[j].T;
            ans = std::max(ans, S[j].W);
        }
        std::cout << ans << std::endl;
    }

    return 0;
}