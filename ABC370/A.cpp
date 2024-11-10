#include <iostream>

int main()
{
    size_t L, R;
    std::cin >> L >> R;
    if (L == 1 && R == 0)
    {
        std::cout << "Yes";
    }
    else if (L == 0 && R == 1)
    {
        std::cout << "No";
    }
    else
    {
        std::cout << "Invalid";
    }
    return 0;
}