#include <iostream>

int main()
{
    int N;
    std::cin >> N;
    if (N % 2 == 0)
    {
        int numWall = (N - 2) / 2;
        for (int i = 0; i < numWall; ++i)
        {
            std::cout << "-";
        }
        std::cout << "==";
        for (int i = 0; i < numWall; ++i)
        {
            std::cout << "-";
        }
    }
    else
    {
        int numWall = (N - 1) / 2;
        for (int i = 0; i < numWall; ++i)
        {
            std::cout << "-";
        }
        std::cout << "=";
        for (int i = 0; i < numWall; ++i)
        {
            std::cout << "-";
        }
    }
    return 0;
}