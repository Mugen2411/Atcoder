#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    size_t N, K;
    std::cin >> N >> K;
    std::vector<size_t> A(N);

    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    std::sort(A.begin(), A.end());

    size_t ans = 5e9;
    for (int i = 0; i <= K; ++i)
    {
        ans = std::min(ans, A[N - K + i - 1] - A[i]);
    }
    std::cout << ans;
    return 0;
}