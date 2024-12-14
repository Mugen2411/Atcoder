#include <iostream>
#include <string>

int main()
{
    int N;
    char c1, c2;
    std::string S;
    std::cin >> N >> c1 >> c2;
    std::cin >> S;

    for (int i = 0; i < N; ++i)
    {
        if (S[i] != c1)
        {
            S[i] = c2;
        }
    }
    std::cout << S;
    return 0;
}