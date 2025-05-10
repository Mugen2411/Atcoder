#include <iostream>

int main()
{
    int R, X;
    std::cin >> X >> R;
    if (R == 1)
    {
        if (1600 <= X && X < 3000)
        {
            std::cout << "Yes";
            return 0;
        }
    }
    else
    {
        if (1200 <= X && X < 2400)
        {
            std::cout << "Yes";
            return 0;
        }
    }
    std::cout << "No";
    return 0;
}