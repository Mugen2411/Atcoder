#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
    std::vector<int> cards(7);
    for (auto &&i : cards)
    {
        std::cin >> i;
    }
    std::unordered_map<int, int> num;
    for (auto i : cards)
    {
        ++num[i];
    }
    bool isOver3 = false;
    for (auto i : num)
    {
        if (i.second >= 3)
        {
            isOver3 = true;
            num.erase(i.first);
            break;
        }
    }
    if (!isOver3)
    {
        std::cout << "No";
        return 0;
    }
    bool isOver2 = false;
    for (auto i : num)
    {
        if (i.second >= 2)
        {
            isOver2 = true;
            num.erase(i.first);
            break;
        }
    }
    if (!isOver2)
    {
        std::cout << "No";
        return 0;
    }
    std::cout << "Yes";
    return 0;
}