#include <iostream>

int main()
{
    size_t N;
    int A;
    char S;

    int beforeL = -1;
    int beforeR = -1;
    size_t ans = 0;
    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A >> S;
        switch (S)
        {
        case 'R':
        {
            if (beforeR < 0)
            {
                beforeR = A;
                break;
            }
            ans += std::abs(beforeR - A);
            beforeR = A;
        }
        break;
        case 'L':
        {
            if (beforeL < 0)
            {
                beforeL = A;
                break;
            }
            ans += std::abs(beforeL - A);
            beforeL = A;
        }
        break;
        }
    }
    std::cout << ans;
    return 0;
}