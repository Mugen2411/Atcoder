#include <iostream>
#include <map>
#include <vector>

struct Query
{
    int64_t x;
    int64_t y;
};

int main()
{
    std::vector<Query> W;
    std::vector<Query> B;
    int64_t N, M;
    std::cin >> N >> M;
    for (int i = 0; i < M; ++i)
    {
        Query tmp;
        char C;
        std::cin >> tmp.x >> tmp.y >> C;
        switch (C)
        {
        case 'W':
            W.push_back(tmp);
            break;
        case 'B':
            B.push_back(tmp);
            break;
        default:
            break;
        }
    }

    std::map<int64_t, int64_t> leftW, upW;
    const int64_t INVALID = 999999;
    leftW[0] = 0;
    upW[0] = 0;
    leftW[N + 1] = 0;
    upW[N + 1] = 0;

    for (auto &w : W)
    {
        if (leftW.count(w.y) == 0)
        {
            leftW[w.y] = (w.x);
        }
        else
        {
            leftW[w.y] = std::min(leftW[w.y], w.x);
        }
        if (upW.count(w.x) == 0)
        {
            upW[w.x] = (w.y);
        }
        else
        {
            upW[w.x] = std::min(upW[w.x], w.y);
        }
    }

    for (auto &b : B)
    {
        {
            auto itr = leftW.lower_bound(b.y);
            if ((*itr).second < b.x)
            {
                std::cout << "No";
                return 0;
            }
        }
        {
            auto itr = upW.lower_bound(b.x);
            if ((*itr).second < b.y)
            {
                std::cout << "No";
                return 0;
            }
        }
    }
    std::cout << "Yes";
    return 0;
}