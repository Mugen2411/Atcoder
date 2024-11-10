#include <iostream>
#include <unordered_set>
#include <algorithm>
#include <string>

int main()
{
    size_t N, Q;
    std::cin >> N >> Q;
    std::string S;
    std::cin >> S;

    std::unordered_set<int64_t> subBeginPos;
    for (int i = 0; i < N - 2; ++i)
    {
        if (S[i] == 'A' && S[i + 1] == 'B' && S[i + 2] == 'C')
        {
            subBeginPos.insert(i);
        }
    }

    while (Q--)
    {
        int64_t X;
        char C;
        std::cin >> X >> C;
        --X;
        S[X] = C;

        for (int64_t i = std::max(X - 2, 0l); i <= X; ++i)
        {
            if (S[i] == 'A' && S[i + 1] == 'B' && S[i + 2] == 'C')
            {
                subBeginPos.insert(i);
            }
            else
            {
                subBeginPos.erase(i);
            }
        }

        std::cout << subBeginPos.size() << std::endl;
    }
}