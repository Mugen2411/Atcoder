#include <iostream>
#include <vector>
#include <unordered_set>

int main()
{
    int N;
    std::cin >> N;
    std::vector<int> A(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    std::vector<std::pair<int64_t, int64_t>> leng;
    for (int i = 0; i < N; ++i)
    {
        if (leng.empty() || leng.back().first != A[i])
        {
            leng.push_back({A[i], 1});
            continue;
        }
        else
        {
            ++leng.back().second;
        }
    }
    std::unordered_set<int> set;
    auto f = [&](int left, int right) -> bool
    {
        if (leng[left].second == 2 && leng[right].second == 2 && set.count(leng[right].first) == 0)
        {
            return true;
        }
        return false;
    };
    int64_t ans = 0;
    int right = 0;
    for (int left = 0; left < leng.size(); ++left)
    {
        while (right < leng.size() && f(left, right))
        {
            set.insert(leng[right].first);
            right++;
        }
        int64_t size = (right - left) * 2;
        if (left > 0 && set.count(leng[left - 1].first) == 0 && leng[left - 1].second > 2)
        {
            size += 2;
        }
        if (right < leng.size() && set.count(leng[right].first) == 0 && leng[right].second > 2)
        {
            size += 2;
        }

        ans = std::max(ans, size);
        if (left == right)
        {
            ++right;
        }
        else
        {
            set.erase(leng[left].first);
        }
    }
    std::cout << ans;
    return 0;
}