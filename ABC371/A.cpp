#include <iostream>

int main()
{
    char S = 0;
    char tmp;
    for (int i = 0; i < 3; ++i)
    {
        S >>= 1;
        std::cin >> tmp;
        if (tmp == '<')
        {
            S |= 4;
        }
    }

    switch (S)
    {
    case 0:
        std::cout << "B";
        return 0;
    case 1:
        std::cout << "A";
        return 0;
    case 2:
        return 0;
    case 3:
        std::cout << "C";
        return 0;
    case 4:
        std::cout << "C";
        return 0;
    case 5:
        return 0;
    case 6:
        std::cout << "A";
        return 0;
    case 7:
        std::cout << "B";
        return 0;
    }

    return 0;
}