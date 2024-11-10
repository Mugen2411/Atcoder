#include <iostream>
#include <vector>

int main()
{
    int N;
    std::cin >> N;
    std::vector<int> A[2];
    A[0].resize(N);
    A[1].resize(N);
    for (int j = 0; j < 2; ++j)
    {
        for (int i = 0; i < N; ++i)
        {
            std::cin >> A[j][i];
        }
    }
    for (int i = 1; i < N; ++i)
    {
        A[0][i] += A[0][i - 1];
    }
    for (int i = N - 1; i > 0; --i)
    {
        A[1][i - 1] += A[1][i];
    }
    int ans = 0;
    for (int i = 0; i < N; ++i)
    {
        if (ans < A[0][i] + A[1][i])
        {
            ans = A[0][i] + A[1][i];
        }
    }
    std::cout << ans << std::endl;
    return 0;
}