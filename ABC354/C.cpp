#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    size_t N;
    std::cin >> N;
    struct CARD
    {
        size_t id;
        size_t attack;
        size_t cost;
    };
    std::vector<CARD> cards(N);
    for (int i = 0; i < N; ++i)
    {
        cards[i].id = i;
        std::cin >> cards[i].attack >> cards[i].cost;
    }
    std::sort(cards.begin(), cards.end(), [](const CARD &lhs, const CARD &rhs)
              { return lhs.cost < rhs.cost; });
    size_t size = cards.size();
    size_t v = 0;
    std::vector<CARD> ans;
    for (int i = 0; i < N; ++i)
    {
        if (cards[i].attack > v)
        {
            ans.push_back(cards[i]);
            v = cards[i].attack;
        }
    }
    std::sort(ans.begin(), ans.end(), [](const CARD &lhs, const CARD &rhs)
              { return lhs.id < rhs.id; });
    std::cout << ans.size() << std::endl;
    for (const auto &itr : ans)
    {
        std::cout << itr.id + 1 << " ";
    }
    return 0;
}