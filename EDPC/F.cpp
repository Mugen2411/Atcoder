#include <iostream>
#include <string>

#define MAX_LEN 3500
int64_t dp[MAX_LEN][MAX_LEN] = {0};

int main()
{
    std::string S, T;
    std::cin >> S;
    std::cin >> T;

    size_t sLen = S.size();
    size_t tLen = T.size();

    for (int s = 1; s <= sLen; ++s)
    {
        for (int t = 1; t <= tLen; ++t)
        {
            if (S[s - 1] == T[t - 1])
            {
                dp[s][t] = std::max(dp[s][t], dp[s - 1][t - 1] + 1);
            }
            dp[s][t] = std::max(dp[s][t], dp[s - 1][t]);
            dp[s][t] = std::max(dp[s][t], dp[s][t - 1]);
        }
    }
    size_t s = sLen;
    size_t t = tLen;
    std::string ans;
    while (s > 0 && t > 0)
    {
        if (dp[s][t] == dp[s - 1][t])
        {
            --s;
            continue;
        }
        else if (dp[s][t] == dp[s][t - 1])
        {
            --t;
            continue;
        }
        else
        {
            ans = S[s - 1] + ans;
            --s, --t;
        }
    }
    std::cout << ans;
    return 0;
}