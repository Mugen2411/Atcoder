#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <algorithm>

int main()
{
    size_t N, M;
    std::cin >> N >> M;
    std::map<size_t, size_t> m;
    size_t A;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A;
        ++m[A];
    }
    std::vector<size_t> B(M);
    for (int i = 0; i < M; ++i)
    {
        std::cin >> B[i];
    }
    std::sort(B.begin(), B.end());
    size_t ans = 0;
    for (int i = 0; i < M; ++i)
    {
        auto itr = m.lower_bound(B[i]);
        if (itr == m.end())
        {
            std::cout << -1;
            return 0;
        }
        ans += itr->first;
        --itr->second;
        if (itr->second == 0)
        {
            m.erase(itr);
        }
    }
    std::cout << ans;
    return 0;
}