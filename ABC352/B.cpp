#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string S, T;
    std::cin >> S >> T;
    std::vector<int> answer(S.size());
    int cur = 0;
    for (int i = 0; i < T.size(); ++i)
    {
        if (T[i] == S[cur])
        {
            answer[cur] = i + 1;
            ++cur;
            if (cur == S.size())
            {
                break;
            }
        }
    }
    for (const auto &i : answer)
    {
        std::cout << i << " ";
    }
    return 0;
}