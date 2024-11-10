#include <iostream>
#include <string>
#include <vector>

int main()
{
    size_t N;
    std::cin >> N;
    std::vector<std::string> S(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> S[i];
    }
    size_t M = 0;
    for (int i = 0; i < N; ++i)
    {
        if (M <= S[i].size())
        {
            M = S[i].size();
        }
    }
    std::vector<size_t> maxN(M);
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (S[j].size() > i)
            {
                maxN[i] = j;
                break;
            }
        }
    }
    for (int m = 0; m < M; ++m)
    {
        for (int i = N - 1; i >= 0; --i)
        {
            if (S[i].size() > m)
            {
                std::cout << S[i][m];
            }
            else
            {
                if (i <= maxN[m])
                {
                    break;
                }
                std::cout << "*";
            }
        }
        std::cout << std::endl;
    }
    return 0;
}