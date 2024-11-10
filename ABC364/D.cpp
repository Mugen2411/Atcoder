#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    size_t N, Q;
    std::cin >> N >> Q;
    std::vector<int64_t> A(N);
    std::vector<int64_t> T(N);
    std::vector<int64_t> B(Q);
    std::vector<int64_t> K(Q);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    std::sort(A.begin(), A.end());
    for (int i = 0; i < Q; ++i)
    {
        std::cin >> B[i] >> K[i];
    }

    for (int i = 0; i < Q; ++i)
    {
        int64_t b = B[i], k = K[i];

        auto f = [&](int64_t x) -> bool
        {
            auto left = std::lower_bound(A.begin(), A.end(), b - x);
            auto right = std::upper_bound(A.begin(), A.end(), b + x);
            return (right - left) >= k;
        };

        int64_t ng = -1e9;
        int64_t ok = 1e9;
        int64_t mid;

        while (ok - ng > 1)
        {
            mid = (ng + ok) / 2;
            if (f(mid))
            {
                ok = mid;
            }
            else
            {
                ng = mid;
            }
        }
        std::cout << ok << std::endl;
    }
    return 0;
}