#include <iostream>
#include <string>

int64_t dp[3][210000] = {0};

int main()
{
    size_t N;
    std::cin >> N;
    std::string S;
    std::cin >> S;

    int64_t inf = 1ll << 60;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 210000; ++j)
        {
            dp[i][j] = -inf;
        }
    }

    size_t r = 0;
    size_t p = 1;
    size_t s = 2;
    switch (S[0])
    {
    case 'R':
    {
        dp[p][0] = 1;
        dp[r][0] = 0;
    }
    break;
    case 'P':
    {
        dp[s][0] = 1;
        dp[p][0] = 0;
    }
    break;
    case 'S':
    {
        dp[r][0] = 1;
        dp[s][0] = 0;
    }
    break;
    }

    for (int i = 1; i < N; ++i)
    {
        switch (S[i])
        {
        case 'R':
        {
            dp[p][i] = std::max(dp[r][i - 1], dp[s][i - 1]) + 1;
            dp[r][i] = std::max(dp[p][i - 1], dp[s][i - 1]);
        }
        break;
        case 'P':
        {
            dp[s][i] = std::max(dp[p][i - 1], dp[r][i - 1]) + 1;
            dp[p][i] = std::max(dp[s][i - 1], dp[r][i - 1]);
        }
        break;
        case 'S':
        {
            dp[r][i] = std::max(dp[s][i - 1], dp[p][i - 1]) + 1;
            dp[s][i] = std::max(dp[p][i - 1], dp[r][i - 1]);
        }
        break;
        }
    }

    std::cout << std::max(dp[r][N - 1], std::max(dp[s][N - 1], dp[p][N - 1]));

    return 0;
}