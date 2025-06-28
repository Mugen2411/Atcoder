#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int N;
        std::cin >> N;
        std::vector<int64_t> S(N - 1);
        int64_t cur;
        for (auto &&s : S)
        {
            std::cin >> s;
        }
        int64_t goal;
        std::cin >> goal;

        std::sort(S.begin() + 1, S.end());

        int64_t ans = 2;
        bool success = false;
        cur = S[0];
        for (int i = 0; i < S.size(); ++i)
        {
            if (cur * 2 >= goal)
            {
                success = true;
                std::cout << ans << std::endl;
                break;
            }

            if (i != S.size() - 1 && S[i + 1] > cur * 2)
            {
                if (cur * 2 < S[i])
                {
                    break;
                }
                if (i != 0 || S[i - 1] != S[i])
                {
                    cur = S[i];
                    ++ans;
                }
            }
            else if (i == S.size() - 1)
            {
                if (S[i] * 2 >= goal)
                {
                    ++ans;
                    success = true;
                    std::cout << ans << std::endl;
                }
                else
                {
                    break;
                }
            }
        }
        if (!success)
        {
            std::cout << -1 << std::endl;
        }
        else
        {
            continue;
        }
    }
    return 0;
}