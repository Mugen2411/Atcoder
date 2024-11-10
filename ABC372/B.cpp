#include <iostream>
#include <vector>

int main()
{
    int64_t M;
    std::cin >> M;
    std::vector<int64_t> ans;
    while (M)
    {
        ans.push_back(M % 3);
        M /= 3;
    }

    size_t sum = 0;
    for (auto &i : ans)
    {
        sum += i;
    }

    std::cout << sum << std::endl;
    for (int i = 0; i < ans.size(); ++i)
    {
        for (int j = 0; j < ans[i]; ++j)
        {
            std::cout << i << " ";
        }
    }
}