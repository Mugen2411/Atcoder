#include <iostream>
#include <map>
#include <algorithm>

int main()
{
    size_t N;
    std::cin >> N;
    std::map<size_t, size_t> A;
    size_t tmp;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> tmp;
        ++A[tmp];
    }
    size_t stock = 0;
    for (auto itr = A.begin(); itr != A.end();)
    {
        if (itr->second > 1)
        {
            stock += itr->second - 1;
            itr->second = 1;
        }
        ++itr;
    }
    size_t ans = 0;
    for (int i = 1; i <= N; ++i)
    {
        if (A.count(i) == 1)
        {
            ++ans;
            A.erase(i);
            continue;
        }
        if (stock >= 2)
        {
            stock -= 2;
            ++ans;
            continue;
        }
        if (stock == 1)
        {
            if (A.size() < 1)
            {
                break;
            }
            --stock;
            A.erase((A.rbegin()->first));
            ++ans;
            continue;
        }
        if (stock == 0)
        {
            if (A.size() < 2)
            {
                break;
            }
            A.erase((A.rbegin()->first));
            A.erase((A.rbegin()->first));
            ++ans;
            continue;
        }
    }
    std::cout << ans << std::endl;
    return 0;
}