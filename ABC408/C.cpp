#include <iostream>
#include <vector>

int main()
{
    int N, M;
    std::cin >> N >> M;
    std::vector<int> wallCover(N + 1, 0);
    while (M--)
    {
        int L, R;
        std::cin >> L >> R;
        wallCover[L - 1]++;
        wallCover[R]--;
    }
    std::vector<int> score(N + 1);
    int cur = 0;
    for (int i = 0; i <= N; ++i)
    {
        cur += wallCover[i];
        score[i] = cur;
    }
    int ans = 999999;
    for (int i = 0; i < N; ++i)
    {
        ans = std::min(ans, score[i]);
    }
    std::cout << ans;
    return 0;
}