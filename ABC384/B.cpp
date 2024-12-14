#include <iostream>

int main()
{
    int N, R;
    std::cin >> N >> R;
    while (N--)
    {
        int D, A;
        std::cin >> D >> A;
        switch (D)
        {
        case 1:
            if (1600 <= R && R < 2800)
            {
                R += A;
            }
            break;
        case 2:
        {
            if (1200 <= R && R < 2400)
            {
                R += A;
            }
        }
        default:
            break;
        }
    }
    std::cout << R;
    return 0;
}