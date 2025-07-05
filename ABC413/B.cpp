#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main()
{
    int N;
    std::cin >> N;
    std::vector<std::string> S(N);
    for (auto &&s : S)
    {
        std::cin >> s;
    }
    std::unordered_set<std::string> dict;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (i == j)
            {
                continue;
            }
            dict.insert(S[i] + S[j]);
        }
    }
    std::cout << dict.size();

    return 0;
}