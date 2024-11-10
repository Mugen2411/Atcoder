#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    size_t N, X;
    std::cin >> N >> X;
    struct Coin
    {
        size_t value;
        size_t num;
    };
    std::vector<Coin> has(N);
    Coin tmp;
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> tmp.value >> tmp.num;
        has[i] = tmp;
    }
    std::sort(has.begin(), has.end(), [](const Coin &lhs, const Coin &rhs)
              { return lhs.value > rhs.value; });
    std::vector<std::vector<bool>> dp(N + 1);
    for (auto &i : dp)
    {
        i.assign(X + 1, false);
    }
    dp[0][0] = true;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 0; j <= X; ++j)
        {
            if (dp[i - 1][j])
            {
                for (int k = 0; k <= has[i - 1].num; ++k)
                {
                    if (j + k * has[i - 1].value > X)
                    {
                        break;
                    }
                    dp[i][j + k * has[i - 1].value] = true;
                }
            }
        }
    }
    if (dp[N][X])
    {
        std::cout << "Yes" << std::endl;
    }
    else
    {
        std::cout << "No" << std::endl;
    }
    return 0;
}