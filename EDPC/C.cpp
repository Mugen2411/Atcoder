#include <iostream>
#include <vector>
#include <array>

int main()
{
    size_t N;
    std::cin >> N;
    std::vector<std::array<size_t, 3>> s(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> s[i][0] >> s[i][1] >> s[i][2];
    }
    std::vector<std::array<size_t, 3>> dp(N + 1);

    dp[0][0] = s[0][0];
    dp[0][1] = s[0][1];
    dp[0][2] = s[0][2];

    for (int i = 1; i < N; ++i)
    {
        dp[i][0] = s[i][0] + std::max(dp[i - 1][1], dp[i - 1][2]);
        dp[i][1] = s[i][1] + std::max(dp[i - 1][0], dp[i - 1][2]);
        dp[i][2] = s[i][2] + std::max(dp[i - 1][1], dp[i - 1][0]);
    }

    std::cout << std::max(std::max(dp[N - 1][0], dp[N - 1][1]), dp[N - 1][2]);
    return 0;
}