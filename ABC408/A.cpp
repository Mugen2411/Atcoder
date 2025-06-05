#include <iostream>

int main()
{
    int N, S;
    std::cin >> N >> S;
    int last = 0;
    while (N--)
    {
        int T;
        std::cin >> T;
        if (T - last > S)
        {
            std::cout << "No";
            return 0;
        }
        last = T;
    }
    std::cout << "Yes";
    return 0;
}