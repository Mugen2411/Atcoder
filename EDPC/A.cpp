#include <iostream>
#include <vector>

int main()
{
    size_t N;
    std::cin >> N;
    std::vector<int64_t> A(N);
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    std::vector<int64_t> dp(N + 1, 1e7);
    dp[0] = 0;
    dp[1] = 0;
    dp[2] = std::abs(A[0] - A[1]);
    for (size_t i = 3; i <= N; ++i)
    {
        dp[i] = std::min(dp[i - 2] + std::abs(A[i - 3] - A[i - 1]), dp[i - 1] + std::abs(A[i - 2] - A[i - 1]));
    }
    std::cout << dp[N];
    return 0;
}