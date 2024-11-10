#include <iostream>
#include <string>

int main()
{
    int N;
    std::cin >> N;
    std::string A[100];
    std::string B[100];
    int tmp;
    for (int y = 0; y < N; ++y)
    {
        std::cin >> A[y];
    }
    for (int y = 0; y < N; ++y)
    {
        std::cin >> B[y];
    }
    for (int y = 0; y < N; ++y)
    {
        for (int x = 0; x < N; ++x)
        {
            if (A[y][x] != B[y][x])
            {
                std::cout << y + 1 << " " << x + 1 << std::endl;
            }
        }
    }

    return 0;
}