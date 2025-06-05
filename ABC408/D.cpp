#include <iostream>
#include <vector>
#include <string>

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int N;
        std::string S;
        std::cin >> N >> S;
        std::vector<int64_t> numZero(N + 1);
        std::vector<int64_t> numOne(N + 1);
        for (int i = 0; i < N; ++i)
        {
            if (S[i] == '0')
            {
                numZero[i + 1] = 1;
            }
            else
            {
                numOne[i + 1] = 1;
            }
        }
        for (int i = 1; i <= N; ++i)
        {
            numZero[i] += numZero[i - 1];
            numOne[i] += numOne[i - 1];
        }
        int64_t score = 9999999;
        for (int i = 1; i <= N; ++i)
        {
            {
                int64_t cur = (numZero[i - 1] - numZero[0]) + (numOne[N] - numOne[i]);
                score = std::min(score, cur);
            }
            {
                int64_t cur = (numOne[i - 1] - numOne[0]) + (numZero[N] - numZero[i]);
                score = std::min(score, cur);
            }
        }

        std::cout << score << std::endl;
    }
    return 0;
}