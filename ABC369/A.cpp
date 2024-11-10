#include <iostream>

int main()
{
    int A, B;
    std::cin >> A >> B;
    if (A == B)
    {
        std::cout << 1;
        return 0;
    }
    if (std::abs(A - B) % 2 != 0)
    {
        std::cout << 2;
        return 0;
    }
    std::cout << 3;
    return 0;
}