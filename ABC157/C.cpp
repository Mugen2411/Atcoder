#include <unordered_map>
#include <iostream>

int main()
{
    int N, M;
    std::cin >> N >> M;
    int s, c;
    std::unordered_map<int, int> map;
    for (int i = 0; i < M; ++i)
    {
        std::cin >> s >> c;
        if (!map.count(s))
        {
            map[s] = c;
        }
        else
        {
            if (map[s] != c)
            {
                std::cout << -1 << std::endl;
                return 0;
            }
        }
    }
    if (map.empty() && N == 1)
    {
        std::cout << 0 << std::endl;
        return 0;
    }
    if (map.count(1) && map[1] == 0)
    {
        if (N == 1)
        {
            std::cout << 0 << std::endl;
            return 0;
        }
        std::cout << -1 << std::endl;
        return 0;
    }
    for (int i = 1; i <= N; ++i)
    {
        if (i == 1 && !map.count(i))
        {
            std::cout << 1;
            continue;
        }
        if (!map.count(i))
        {
            std::cout << 0;
            continue;
        }
        std::cout << map[i];
    }
    std::cout << std::endl;
    return 0;
}