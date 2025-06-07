#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

int main()
{
    int N, L;
    std::cin >> N >> L;
    if (L % 3 != 0)
    {
        std::cout << 0;
        return 0;
    }
    int edge = L / 3;
    std::vector<int> d(N - 1);
    for (auto &&i : d)
    {
        std::cin >> i;
    }
    d.insert(d.begin(), 0);

    for (int i = 1; i < N; ++i)
    {
        d[i] = (d[i] + d[i - 1]) % L;
    }

    std::unordered_map<int, int64_t> num;
    for (int i = 0; i < N; ++i)
    {
        ++num[d[i]];
    }
    std::sort(d.begin(), d.end());
    auto uq = std::unique(d.begin(), d.end());
    d.erase(uq, d.end());

    int64_t ans = 0;
    for (int i = 0; i < d.size(); ++i)
    {
        int cur = d[i];
        int d2 = (cur + edge) % L;
        int d3 = (cur + edge * 2) % L;

        if (cur >= edge)
        {
            break;
        }

        if (num.count(d2) != 0 && num.count(d3) != 0)
        {
            ans += num[cur] * num[d2] * num[d3];
        }
    }
    std::cout << ans;
    return 0;
}