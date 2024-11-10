#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    size_t N, Q;
    std::cin >> N >> Q;
    std::vector<size_t> R(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> R[i];
    }
    std::sort(R.begin(), R.end());
    for (int i = 1; i < N; ++i)
    {
        R[i] = R[i] + R[i - 1];
    }
    size_t X;
    for (int i = 0; i < Q; ++i)
    {
        std::cin >> X;
        auto itr = std::upper_bound(R.begin(), R.end(), X);
        size_t ans = std::distance(R.begin(), itr);
        std::cout << ans << std::endl;
    }
    return 0;
}