#include <iostream>
#include <unordered_map>

int main()
{
    size_t Q;
    std::cin >> Q;
    std::unordered_map<size_t, size_t> um;
    for (int q = 0; q < Q; ++q)
    {
        size_t command;
        std::cin >> command;

        switch (command)
        {
        case 1:
        {
            size_t x;
            std::cin >> x;
            um[x]++;
        }
        break;
        case 2:
        {
            size_t x;
            std::cin >> x;
            um[x]--;
            if (um[x] == 0)
            {
                um.erase(x);
            }
        }
        break;
        case 3:
        {
            std::cout << um.size() << std::endl;
        }
        }
    }
    return 0;
}