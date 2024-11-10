#include <iostream>
#include <vector>

int main()
{
    size_t N, M;
    std::cin >> N >> M;
    std::vector<size_t> A(N * 2 + 1, 0);
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> A[i];
        A[i + N] = A[i];
        A[i] += A[i - 1];
        A[i] %= M;
    }
    for (int i = N + 1; i <= 2 * N; ++i)
    {
        A[i] += A[i - 1];
        A[i] %= M;
    }
    size_t ans = 0;
    for (int i = 1; i <= N; ++i)
    {
        }
    std::cout << ans;
    return 0;
}