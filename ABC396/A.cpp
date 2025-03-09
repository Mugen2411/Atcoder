#include <iostream>
#include <vector>

int main()
{
    size_t N;
    std::cin >> N;
    std::vector<int64_t> A(N);
    for (auto &&a : A)
    {
        std::cin >> a;
    }
    for (int i = 0; i < N - 2; ++i)
    {
        if (A[i] == A[i + 1] && A[i + 1] == A[i + 2])
        {
            std::cout << "Yes" << std::endl;
            return 0;
        }
    }
    std::cout << "No" << std::endl;
    return 0;
}