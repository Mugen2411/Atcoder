#include <iostream>
#include <vector>

int main()
{
    int N;
    std::cin >> N;
    std::vector<int64_t> P(N);
    for (auto &&p : P)
    {
        std::cin >> p;
    }
    std::vector<int> isIncreasing(N - 1);
    for (int i = 1; i < N; ++i)
    {
        if (P[i - 1] > P[i])
        {
            isIncreasing[i - 1] = -1;
        }
        else
        {
            isIncreasing[i - 1] = 1;
        }
    }
    struct Elem
    {
        int isIncresing;
        int64_t num;
    };
    std::vector<Elem> leng;
    for (int i = 0; i < N - 1; ++i)
    {
        if (i == 0 || leng.back().isIncresing != isIncreasing[i])
        {
            leng.push_back({isIncreasing[i], 1});
        }
        else
        {
            ++leng.back().num;
        }
    }
    int64_t ans = 0;
    for (int i = 1; i < leng.size() - 1; ++i)
    {
        if (leng[i].isIncresing == -1)
        {
            ans += leng[i - 1].num * leng[i + 1].num;
        }
    }
    std::cout << ans;
    return 0;
}