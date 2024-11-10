#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    size_t N, X, Y;
    std::cin >> N >> X >> Y;
    using meal_t = std::pair<size_t, size_t>;
    std::vector<meal_t> meal(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> meal[i].first;
    }
    for (int i = 0; i < N; ++i)
    {
        std::cin >> meal[i].second;
    }

    std::sort(meal.begin(), meal.end(), [](const meal_t &lhs, const meal_t &rhs)
              { return lhs.first > rhs.first; });
    size_t minSweet = 0;
    size_t curSweet = 0;
    size_t curSalty = 0;
    for (int i = 0; i < N; ++i)
    {
        if (curSweet <= X && curSalty <= Y)
        {
            minSweet++;
        }
        curSweet += meal[i].first;
        curSalty += meal[i].second;
    }

    std::sort(meal.begin(), meal.end(), [](const meal_t &lhs, const meal_t &rhs)
              { return lhs.second > rhs.second; });
    size_t minSalty = 0;
    curSweet = 0;
    curSalty = 0;
    for (int i = 0; i < N; ++i)
    {
        if (curSweet <= X && curSalty <= Y)
        {
            minSalty++;
        }
        curSweet += meal[i].first;
        curSalty += meal[i].second;
    }
    std::cout << std::min(minSalty, minSweet);
    return 0;
}