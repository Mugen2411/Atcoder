#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int Q;
    std::cin >> Q;
    std::vector<int64_t> q;
    while (Q--)
    {
        int cmd;
        std::cin >> cmd;
        switch (cmd)
        {
        case 1:
            q.push_back(0);
            break;
        case 2:
        {
            int64_t T;
            std::cin >> T;
            for (auto &i : q)
            {
                i += T;
            }
        }
        break;
        case 3:
        {
            int64_t H;
            std::cin >> H;
            int64_t ans = 0;
            std::sort(q.begin(), q.end());
            auto itr = std::lower_bound(q.begin(), q.end(), H);
            if (itr == q.end())
            {
                std::cout << 0 << std::endl;
                break;
            }
            ans = q.end() - itr;
            std::cout << ans << std::endl;
            while (ans--)
            {
                q.pop_back();
            }
        }
        break;
        }
    }
    return 0;
}