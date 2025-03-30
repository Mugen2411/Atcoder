#include <iostream>
#include <string>

int main()
{
    int N;
    std::cin >> N;
    std::string S, T;
    std::cin >> S >> T;
    int ans = 0;
    for (int i = 0; i < N; ++i)
    {
        if (S[i] != T[i])
        {
            ++ans;
        }
    }
    std::cout << ans;
    return 0;
}