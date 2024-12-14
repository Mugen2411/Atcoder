#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

int main()
{
    char tag[5] = {'A', 'B', 'C', 'D', 'E'};
    int64_t score[5];
    std::cin >> score[0] >> score[1] >> score[2] >> score[3] >> score[4];

    std::vector<std::pair<std::string, int64_t>> vec(32);

    for (int i = 0; i < 32; ++i)
    {
        int scr = 0;
        std::string name;
        for (int j = 0; j < 5; ++j)
        {
            if (i & (1 << j))
            {
                scr += score[j];
                name += tag[j];
            }
        }
        vec[i].first = name;
        vec[i].second = scr;
    }

    std::stable_sort(vec.begin(), vec.end(), [](const std::pair<std::string, int64_t> &lhs, const std::pair<std::string, int64_t> &rhs)
                     { return lhs.first < rhs.first; });
    std::stable_sort(vec.begin(), vec.end(), [](const std::pair<std::string, int64_t> &lhs, const std::pair<std::string, int64_t> &rhs)
                     { return lhs.second > rhs.second; });

    for (auto &i : vec)
    {
        std::cout << i.first << std::endl;
    }
    return 0;
}