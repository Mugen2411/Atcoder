#include <iostream>
#include <string>

int main()
{
    std::string D;
    std::cin >> D;
    for (auto &c : D)
    {
        switch (c)
        {
        case 'N':
            c = 'S';
            break;

        case 'S':
            c = 'N';
            break;

        case 'E':
            c = 'W';
            break;

        case 'W':
            c = 'E';
            break;
        }
    }
    std::cout << D;
    return 0;
}