#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string T;
    std::cin >> T;
    size_t dp[105][105];
    for (int i = 0; i < 105; ++i)
    {
        for (int j = 0; j < 105; ++j)
        {
            dp[i][j] = 1e9;
        }
    }
    dp[0][0] = 0;
    int N;
    std::cin >> N;
    std::vector<std::string> S[105];
    for (int i = 0; i < N; ++i)
    {
        int A;
        std::cin >> A;
        S[i].resize(A);
        for (int j = 0; j < A; ++j)
        {
            std::cin >> S[i][j];
        }
    }

    // dp[処理した袋の数][一致させた文字数]
    for (int i = 0; i < N; ++i)
    {
        // 袋S[i]から文字列を取らない
        for (int j = 0; j < 105; ++j)
        {
            dp[i + 1][j] = dp[i][j];
        }
        for (int a = 0; a < S[i].size(); ++a)
        {
            size_t slen = S[i][a].size();
            for (int j = 0; j + slen <= T.size(); ++j)
            {
                bool same = true;
                for (int s = 0; s < slen; ++s)
                {
                    if (T[j + s] != S[i][a][s])
                    {
                        same = false;
                        break;
                    }
                }
                if (same)
                {
                    dp[i + 1][j + slen] = std::min(dp[i + 1][j + slen], dp[i][j] + 1);
                }
            }
        }
    }
    if (dp[N][T.size()] > 5e8)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << dp[N][T.size()];
    }
    return 0;
}