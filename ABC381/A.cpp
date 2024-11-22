#include <iostream>
#include <string>

int main()
{
    int N;
    std::string S;
    std::cin >> N >> S;
    if (N % 2 == 0)
    {
        std::cout << "No";
        return 0;
    }
    int half = (N - 1) / 2;
    int i = 0;
    for (; i < half; ++i)
    {
        if (S[i] != '1')
        {
            std::cout << "No";
            return 0;
        }
    }
    if (S[i] != '/')
    {
        std::cout << "No";
        return 0;
    }
    ++i;
    int cur = i;
    for (; i < cur + half; ++i)
    {
        if (S[i] != '2')
        {
            std::cout << "No";
            return 0;
        }
    }
    std::cout << "Yes";
    return 0;
}