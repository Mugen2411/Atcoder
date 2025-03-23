#include <iostream>
#include <string>
#include <unordered_set>

struct POSITION
{
    int64_t x, y;
    bool operator==(const POSITION &rhs)
    {
        return x == rhs.x && y == rhs.y;
    }
};

bool operator==(const POSITION &lhs, const POSITION &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

namespace std
{
    template <>
    class hash<POSITION>
    {
    public:
        size_t operator()(const POSITION &p) const { return p.x ^ p.y; }
    };
}

int main()
{
    int64_t N, R, C;
    std::cin >> N >> R >> C;
    std::string S;
    std::cin >> S;

    int64_t bX = 0, bY = 0;

    std::unordered_set<POSITION> set;
    set.insert({bX, bY});

    for (auto i : S)
    {
        switch (i)
        {
        case 'N':
            ++R;
            ++bY;
            break;
        case 'S':
            --R;
            --bY;
            break;
        case 'E':
            --C;
            --bX;
            break;
        case 'W':
            ++C;
            ++bX;
            break;

        default:
            break;
        }

        set.insert({bX, bY});

        if (set.count({C, R}) != 0)
        {
            std::cout << "1";
        }
        else
        {
            std::cout << "0";
        }
    }
    return 0;
}