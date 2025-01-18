#include <iostream>

int main()
{
    int64_t N;
    std::cin >> N;
    int64_t ans = 1;
    for (int i = 2;; ++i)
    {
        ans *= i;
        if (N == ans)
        {
            std::cout << i;
            return 0;
        }
    }
    return 0;
}