#include <iostream>
#include <list>

int main()
{
    struct ELEM
    {
        int64_t value;
        int64_t num;
    };
    std::list<ELEM> ls;
    int Q;
    std::cin >> Q;
    while (Q--)
    {
        int cmd;
        std::cin >> cmd;
        switch (cmd)
        {
        case 1:
        {
            int64_t c, x;
            std::cin >> c >> x;
            ls.push_back(ELEM{x, c});
        }
        break;

        case 2:
        {
            int64_t k;
            std::cin >> k;
            int64_t ans = 0;
            while (k > 0)
            {
                ELEM &top = ls.front();
                if (top.num <= k)
                {
                    ans += top.value * top.num;
                    k -= top.num;
                    ls.pop_front();
                }
                else
                {
                    ans += top.value * k;
                    top.num -= k;
                    k = 0;
                }
            }
            std::cout << ans << std::endl;
        }
        break;
        default:
            break;
        }
    }
    return 0;
}