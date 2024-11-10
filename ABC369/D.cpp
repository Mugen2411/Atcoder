#include <iostream>
#include <vector>
#include <array>

int main()
{
    size_t N;
    std::cin >> N;
    std::vector<size_t> A(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    std::vector<std::array<std::array<size_t, 2>, 2>> dp(N + 1);
    dp[0][0] = {0, 0};
    dp[0][1] = {0, 0};
    for (int i = 0; i < N; ++i)
    {
        if (dp[i][0][0] < dp[i][1][0])
        {
            dp[i + 1][0] = dp[i][1];
        }
        else
        {
            dp[i + 1][0] = dp[i][0];
        }
        size_t from0 = dp[i][0][0] + A[i] * (1 + dp[i][0][1]);
        size_t from1 = dp[i][1][0] + A[i] * (1 + dp[i][1][1]);
        if (from0 < from1)
        {
            dp[i + 1][1] = {from1, dp[i][1][1] ^ 1};
        }
        else
        {
            dp[i + 1][1] = {from0, dp[i][0][1] ^ 1};
        }
    }
    std::cout << std::max(dp[N][0][0], dp[N][1][0]);
    return 0;
}