#include <iostream>

int main()
{
    double X;
    std::cin >> X;
    if (X < 37.5)
    {
        std::cout << "3";
    }
    else if (X < 38.0)
    {
        std::cout << "2";
    }
    else
    {
        std::cout << "1";
    }
    return 0;
}