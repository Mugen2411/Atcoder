#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

template <class F>
int64_t BinarySearch(int64_t ng, int64_t ok, F comp)
{
    int64_t mid;
    while (std::abs(ng - ok) > 1)
    {
        mid = (ng + ok) / 2;
        if (comp(mid))
        {
            ok = mid;
        }
        else
        {
            ng = mid;
        }
    }
    return ok;
}

int main()
{
    int64_t N, M, K;
    std::cin >> N >> M >> K;
    int64_t k = K;
    std::vector<int64_t> A(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
        k -= A[i];
    }
    std::vector<int64_t> sorted(A);
    std::sort(sorted.begin(), sorted.end(), std::greater<int64_t>());
    sorted.insert(sorted.begin(), 0);

    for (int i = 1; i <= N; ++i)
    {
        sorted[i] += sorted[i - 1];
    }

    std::vector<int64_t> C(N, -1);

    for (int i = 0; i < N; ++i)
    {
        int64_t ans = BinarySearch(-1, 1e13,
                                   [&](int64_t mid)
                                   {
                                       int64_t tk;
                                       tk = (mid + 1) * M - (sorted[M] - sorted[0]);

                                       return tk > k - (mid - A[i]);
                                   });

        if (ans <= A[i])
        {
            C[i] = 0;
        }
        else if (ans - A[i] > k)
        {
            C[i] = -1;
        }
        else
        {
            C[i] = ans - A[i];
        }
    }

    for (auto &c : C)
    {
        std::cout << c << " ";
    }
    return 0;
}