#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string S;
    std::cin >> S;
    std::vector<int> ans;
    int tmp = 0;
    for (int i = 1; i < S.size(); ++i)
    {
        if (S[i] == '-')
        {
            ++tmp;
        }
        if (S[i] == '|')
        {
            ans.push_back(tmp);
            tmp = 0;
        }
    }
    for (auto i : ans)
    {
        std::cout << i << " ";
    }
    return 0;
}