#include <iostream>
#include <vector>

int main()
{
    size_t N, M;
    std::cin >> N >> M;
    std::vector<size_t> A(M);
    std::vector<size_t> gained(M);
    for (int i = 0; i < M; ++i)
    {
        std::cin >> A[i];
    }
    size_t tmp;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            std::cin >> tmp;
            gained[j] += tmp;
        }
    }

    for (int i = 0; i < M; ++i)
    {
        if (gained[i] < A[i])
        {
            std::cout << "No";
            return 0;
        }
    }
    std::cout << "Yes";

    return 0;
}