#include <iostream>
#include <iomanip>

double dp[3200][3200] = {0.0};

int main()
{
    size_t N;
    double p[3200] = {0.0};
    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> p[i];
    }

    dp[0][0] = 1.0;

    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            dp[i][j] += dp[i - 1][j - 1] * p[i - 1];
            dp[i][j - 1] += dp[i - 1][j - 1] * (1.0 - p[i - 1]);
        }
    }

    double ans = 0.0;
    for (int i = N / 2 + 1; i <= N; ++i)
    {
        ans += dp[N][i];
    }
    std::cout << std::fixed << std::setprecision(10) << ans;
    return 0;
}