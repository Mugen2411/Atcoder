#include <iostream>
#include <vector>

int main()
{
    size_t N, K;
    std::cin >> N >> K;
    std::vector<int64_t> A(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }

    std::vector<int64_t> dp(N + K, 1LL << 60);
    dp[0] = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 1; j <= K; ++j)
        {
            dp[i + j] = std::min(dp[i + j], dp[i] + std::abs(A[i + j] - A[i]));
        }
    }
    std::cout << dp[N - 1];
    return 0;
}