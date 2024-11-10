#include <iostream>

int main()
{
    int A, B, C;
    std::cin >> A >> B >> C;
    bool T[24] = {false};
    for (int i = B; i != C; ++i, i %= 24)
    {
        T[i] = true;
    }
    if (T[A])
    {
        std::cout << "No";
    }
    else
    {
        std::cout << "Yes";
    }
    return 0;
}