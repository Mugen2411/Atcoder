#include <iostream>

int main()
{
    size_t N, K, X;
    std::cin >> N >> K >> X;
    size_t tmp;
    size_t A[101];
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    for (int i = 0; i < N; ++i)
    {
        std::cout << A[i] << " ";
        if (i == K - 1)
        {
            std::cout << X << " ";
        }
    }
    return 0;
}