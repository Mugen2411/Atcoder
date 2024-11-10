#include <iostream>

int main()
{
    size_t N, A;
    std::cin >> N >> A;
    size_t cur = 0;
    size_t T;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> T;
        if (T > cur)
        {
            cur = T + A;
        }
        else
        {
            cur += A;
        }
        std::cout << cur << std::endl;
    }
    return 0;
}