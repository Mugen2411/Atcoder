#include <iostream>
#include <vector>

int main()
{
    size_t N, K;
    std::cin >> N >> K;
    std::vector<size_t> A(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    int begin = 0, end = N;
    int mid;
    while (end - begin > 1)
    {
        mid = (begin + end) / 2;

        if (A[mid] >= K)
        {
            end = mid;
        }
        else
        {
            begin = mid;
        }
    }
    if (A[end] < K)
    {
        std::cout << -1;
        return 0;
    }
    std::cout << end;
    return 0;
}