#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::string S, T;
    std::cin >> S >> T;
    std::vector<std::string> X;
    size_t len = S.size();
    while (S != T)
    {
        std::vector<std::string> tmp;
        for (int i = 0; i < len; ++i)
        {
            if (S[i] != T[i])
            {
                tmp.push_back(S);
                tmp.back()[i] = T[i];
            }
        }
        std::sort(tmp.begin(), tmp.end());
        X.push_back(tmp.front());
        S = tmp.front();
    }
    std::cout << X.size() << std::endl;
    for (const auto &s : X)
    {
        std::cout << s << std::endl;
    }
    return 0;
}