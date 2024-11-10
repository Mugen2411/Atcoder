#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int N;
    std::cin >> N;
    std::vector<size_t> A(N);
    size_t S = 0, S2 = 0;
    const size_t MOD = 100000000;
    size_t cnt = 0;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
        S += A[i];
    }

    S *= (N - 1); // とりあえず総和

    // ここから二分探索で1e8超える組み合わせの個数を数える
    std::sort(A.begin(), A.end());

    for (int i = 0; i < N - 1; ++i)
    {
        auto pos = std::lower_bound(A.begin() + i + 1, A.end(), MOD - A[i]);
        if (pos == A.end())
        {
            continue;
        }
        size_t diff = A.size() - std::distance(A.begin(), pos);
        cnt += diff;
    }

    std::cout << S - MOD * cnt << std::endl;
    return 0;
}