#include <iostream>

int main()
{
    int A, B, C;
    std::cin >> A >> B >> C;
    if (A == B && B == C)
    {
        std::cout << "Yes" << std::endl;
        return 0;
    }

    if (A == B + C || B == A + C || C == A + B)
    {
        std::cout << "Yes" << std::endl;
        return 0;
    }
    std::cout << "No" << std::endl;
    return 0;
}