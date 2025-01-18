#include <iostream>
#include <vector>

int main()
{
    int64_t Q;
    std::cin >> Q;
    int64_t dead = 0;
    std::vector<int64_t> v;
    v.push_back(0);
    int64_t cur = 0;
    while (Q--)
    {
        int cmd;
        std::cin >> cmd;
        switch (cmd)
        {
        case 1:
        {
            int64_t l;
            std::cin >> l;
            {
                v.push_back(v.back() + l);
            }
        }
        break;
        case 2:
        {
            ++cur;
            dead = v[cur];
        }
        break;
        case 3:
        {
            int64_t k;
            std::cin >> k;
            --k;
            std::cout << v[k + cur] - dead << std::endl;
        }
        default:
            break;
        }
    }
    return 0;
}