#include <iostream>

int main()
{
    const int loopLimit7 = 100 / 7;
    const int loopLimit4 = 100 / 4;

    int N;

    std::cin >> N;

    for (int i7 = 0; i7 < loopLimit7; ++i7)
    {
        for (int i4 = 0; i4 < loopLimit4; ++i4)
        {
            if (i7 * 7 + i4 * 4 == N)
            {
                std::cout << "Yes" << std::endl;
                return 0;
            }
        }
    }
    std::cout << "No" << std::endl;
    return 0;
}