#include <iostream>
#include <string>

int main()
{
    int N, D;
    std::string S;
    std::cin >> N >> D;
    std::cin >> S;

    int sum = 0;
    for (int i = 0; i < N; ++i)
    {
        if (S[i] == '@')
        {
            ++sum;
        }
    }

    std::cout << std::max(0, N - sum + D);

    return 0;
}