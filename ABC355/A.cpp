#include <iostream>

int main()
{
    int A, B;
    std::cin >> A >> B;
    int a[3] = {0};
    a[A - 1] = 1;
    a[B - 1] = 1;
    if (A == B)
    {
        std::cout << -1 << std::endl;
        return 0;
    }
    for (int i = 0; i < 3; ++i)
    {
        if (a[i] == 0)
        {
            std::cout << i + 1 << std::endl;
            return 0;
        }
    }
}