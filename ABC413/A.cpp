#include <iostream>

int main()
{
    int N, M;
    std::cin >> N >> M;
    int sum = 0;
    while (N--)
    {
        int tmp;
        std::cin >> tmp;
        sum += tmp;
    }
    if (sum <= M)
    {
        std::cout << "Yes";
    }
    else
    {
        std::cout << "No";
    }
    return 0;
}