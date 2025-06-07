#include <iostream>
#include <string>

int main()
{
    int N;
    std::string S;
    std::string T;
    std::cin >> N >> S >> T;
    for (int i = 0; i < N; ++i)
    {
        if (S[i] == 'o' && T[i] == 'o')
        {
            std::cout << "Yes";
            return 0;
        }
    }
    std::cout << "No";
    return 0;
}