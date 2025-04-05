#include <iostream>

int main()
{
    int A;
    std::cin >> A;
    if (400 % A != 0)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << 400 / A;
    }
    return 0;
}