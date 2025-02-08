#include <iostream>

int main()
{
    int A1, A2, A3;
    std::cin >> A1 >> A2 >> A3;
    if (A1 * A2 == A3 || A2 * A3 == A1 || A3 * A1 == A2)
    {
        std::cout << "Yes";
    }
    else
    {
        std::cout << "No";
    }
    return 0;
}