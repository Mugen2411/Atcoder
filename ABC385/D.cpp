#include <iostream>
#include <set>
#include <unordered_map>
#include <limits>

int main()
{
    int64_t N, M, sX, sY;
    std::cin >> N >> M >> sX >> sY;

    std::unordered_map<int64_t, std::set<int64_t>> verticalSanta, horizontalSanta;
    int64_t invalid = std::numeric_limits<int64_t>::max();
    while (N--)
    {
        int X, Y;
        std::cin >> X >> Y;
        verticalSanta[X].insert(Y);
        horizontalSanta[Y].insert(X);
    }

    int64_t ans = 0;
    while (M--)
    {
        char D;
        int64_t C;
        std::cin >> D >> C;
        switch (D)
        {
        case 'U':
        {
            int64_t nextY = sY + C;

            auto itr = verticalSanta[sX].lower_bound(sY);
            while (itr != verticalSanta[sX].end() && *itr <= nextY)
            {
                ++ans;
                if (horizontalSanta.count(*itr))
                {
                    horizontalSanta[*itr].erase(sX);
                }
                itr = verticalSanta[sX].erase(itr);
            }

            sY = nextY;
        }
        break;
        case 'D':
        {
            int64_t nextY = sY - C;

            auto itr = verticalSanta[sX].lower_bound(nextY);
            while (itr != verticalSanta[sX].end() && *itr <= sY)
            {
                ++ans;
                if (horizontalSanta.count(*itr))
                {
                    horizontalSanta[*itr].erase(sX);
                }
                itr = verticalSanta[sX].erase(itr);
            }

            sY = nextY;
        }
        break;
        case 'L':
        {
            int64_t nextX = sX - C;

            auto itr = horizontalSanta[sY].lower_bound(nextX);
            while (itr != horizontalSanta[sY].end() && *itr <= sX)
            {
                ++ans;
                if (verticalSanta.count(*itr))
                {
                    verticalSanta[*itr].erase(sY);
                }
                itr = horizontalSanta[sY].erase(itr);
            }

            sX = nextX;
        }
        break;
        case 'R':
        {
            int64_t nextX = sX + C;

            auto itr = horizontalSanta[sY].lower_bound(sX);
            while (itr != horizontalSanta[sY].end() && *itr <= nextX)
            {
                ++ans;
                if (verticalSanta.count(*itr))
                {
                    verticalSanta[*itr].erase(sY);
                }
                itr = horizontalSanta[sY].erase(itr);
            }

            sX = nextX;
        }
        break;
        default:
            break;
        }
    }
    std::cout << sX << ' ' << sY << ' ' << ans;
    return 0;
}