#include <iostream>

int main()
{
    size_t N, Q;
    std::cin >> N >> Q;
    int64_t curL = 0;
    int64_t curR = 1;
    int64_t ans = 0;
    while (Q--)
    {
        char H;
        int64_t T;
        std::cin >> H >> T;
        --T;
        switch (H)
        {
        case 'R':
        {
            int64_t costR = [&]()
            {
                int64_t cost = 0;
                int64_t cur = curR;
                while (cur != T)
                {
                    ++cur;
                    if (cur >= N)
                    {
                        cur = 0;
                    }
                    if (cur == curL)
                    {
                        cost += 9999999;
                    }
                    ++cost;
                }
                return cost;
            }();
            int64_t costL = [&]()
            {
                int64_t cost = 0;
                int64_t cur = curR;
                while (cur != T)
                {
                    --cur;
                    if (cur < 0)
                    {
                        cur = N - 1;
                    }
                    if (cur == curL)
                    {
                        cost += 9999999;
                    }
                    ++cost;
                }
                return cost;
            }();

            ans += std::min(costL, costR);

            curR = T;
        }
        break;
        case 'L':
        {
            int64_t costR = [&]()
            {
                int64_t cost = 0;
                int64_t cur = curL;
                while (cur != T)
                {
                    ++cur;
                    if (cur >= N)
                    {
                        cur = 0;
                    }
                    if (cur == curR)
                    {
                        cost += 9999999;
                    }
                    ++cost;
                }
                return cost;
            }();
            int64_t costL = [&]()
            {
                int64_t cost = 0;
                int64_t cur = curL;
                while (cur != T)
                {
                    --cur;
                    if (cur < 0)
                    {
                        cur = N - 1;
                    }
                    if (cur == curR)
                    {
                        cost += 9999999;
                    }
                    ++cost;
                }
                return cost;
            }();

            ans += std::min(costL, costR);
            curL = T;
        }
        break;

        default:
            break;
        }
    }

    std::cout << ans;
    return 0;
}