#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

/*
10
4 8 3 2 1 5 9 7 10 6
*/
int main()
{
    size_t N;
    std::cin >> N;
    std::vector<int> vec(N);
    std::vector<std::array<int, 2>> commandList;
    int tmp;
    int cnt = 0;
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> vec[i];
        --vec[i];
    }

    for (int i = 0; i < N; ++i)
    {
        while (vec[i] != i)
        {

            commandList.push_back({std::min(i, vec[i]) + 1, std::max(i, vec[i]) + 1});
            tmp = vec[vec[i]];
            vec[vec[i]] = vec[i];
            vec[i] = tmp;

            ++cnt;
        }
    }

    std::cout << cnt << std::endl;
    for (const auto &cmd : commandList)
    {
        std::cout << cmd[0] << " " << cmd[1] << std::endl;
    }

    return 0;
}