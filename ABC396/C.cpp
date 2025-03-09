#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    size_t N, M;
    std::cin >> N >> M;
    std::vector<int64_t> B(N);
    std::vector<int64_t> W(M);
    for (auto &&b : B)
    {
        std::cin >> b;
    }
    for (auto &&w : W)
    {
        std::cin >> w;
    }

    std::sort(B.begin(), B.end(), std::greater<int64_t>());
    std::sort(W.begin(), W.end(), std::greater<int64_t>());

    B.insert(B.begin(), 0);
    W.insert(W.begin(), 0);

    for (int i = 1; i <= N; ++i)
    {
        B[i] += B[i - 1];
    }
    for (int i = 1; i <= M; ++i)
    {
        W[i] += W[i - 1];
    }

    std::vector<int64_t> maxW(M + 1, 0);
    for (int i = 1; i <= M; ++i)
    {
        maxW[i] = std::max(W[i], maxW[i - 1]);
    }

    int64_t ans = 0;
    for (size_t i = 0; i <= N; ++i)
    {
        ans = std::max(ans, B[i] + maxW[std::min(i, M)]);
    }
    std::cout << ans;
    return 0;
}