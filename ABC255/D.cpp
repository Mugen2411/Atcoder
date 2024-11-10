#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int64_t N, Q;
    std::cin >> N >> Q;
    std::vector<int64_t> A(N);
    std::vector<int64_t> sum(N + 1);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    std::sort(A.begin(), A.end());
    sum[0] = 0;
    for (int i = 0; i < N; ++i)
    {
        sum[i + 1] = A[i] + sum[i];
    }
    for (int i = 0; i < Q; ++i)
    {
        int64_t q;
        std::cin >> q;
        auto itr = std::lower_bound(A.begin(), A.end(), q);
        int64_t idx = itr - A.begin();
        int64_t left = q * idx - sum[idx] + sum[0];
        int64_t right = (sum[N] - sum[idx]) - q * (N - idx);
        std::cout << left + right << std::endl;
    }
    return 0;
}