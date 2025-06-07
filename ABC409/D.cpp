#include <iostream>
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
        int l = -1;
        for (int i = 0; i < N - 1; ++i)
        {
            if (S[i] > S[i + 1])
            {
                l = i;
                break;
            }
        }
        // 元から最強のパターン
        if (l == -1)
        {
            std::cout << S << std::endl;
            continue;
        }
        int r = -1;
        for (int i = l + 1; i < N; ++i)
        {
            if (S[l] < S[i])
            {
                r = i;
                break;
            }
        }
        // ケツにつけるしかないパターン
        if (r == -1)
        {
            char tmp = S[l];
            S.erase(S.begin() + l);
            S.push_back(tmp);
            std::cout << S << std::endl;
            continue;
        }
        // 途中に割り込むパターン
        char tmp = S[l];
        S.erase(S.begin() + l);
        S.insert(S.begin() + r - 1, tmp);
        std::cout << S << std::endl;
        continue;
    }
    return 0;
}