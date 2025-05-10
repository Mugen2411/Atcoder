#include <iostream>
#include <vector>

int main()
{
    int N;
    std::cin >> N;
    std::vector<int64_t> A(N);
    for (auto &&a : A)
    {
        std::cin >> a;
    }
    int64_t oneLine = 0;
    for (int i = 0; i < N; ++i)
    {
        oneLine += A[i];
    }
    int64_t ans = 0;
    for (int i = 0; i < N; ++i)
    {
        ans += oneLine * A[i];
    }
    int64_t slash = 0;
    for (int i = 0; i < N; ++i)
    {
        slash += A[i] * A[i];
    }
    std::cout << (ans - slash) / 2;
    return 0;
}