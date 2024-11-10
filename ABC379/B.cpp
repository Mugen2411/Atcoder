#include <iostream>
#include <string>
#include <vector>

int main()
{
    int N, K;
    std::string S;

    std::cin >> N >> K;
    std::cin >> S;

    std::vector<int> cont;
    int c = 0;
    for (int i = 0; i < N; ++i)
    {
        if (S[i] == 'O')
        {
            ++c;
        }
        else
        {
            if (c == 0)
            {
                continue;
            }
            cont.push_back(c);
            c = 0;
        }
    }
    if (c != 0)
    {
        cont.push_back(c);
    }

    int ans = 0;
    for (auto &i : cont)
    {
        ans += i / K;
    }
    std::cout << ans;

    return 0;
}