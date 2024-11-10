#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
    std::string S;
    std::cin >> S;

    int64_t N = S.size();

    std::vector<int64_t> dic[26];
    for (int i = 0; i < N; ++i)
    {
        dic[S[i] - 'A'].push_back(i);
    }
    size_t ans = 0;

    auto f = [&](int left, int right)
    {
        return S[left] == S[right];
    };

    int right = 2;
    for (int left = 0; left < N; ++left)
    {
        while (right < N && f(left, right))
        {
            right++;
        }

        auto &d = dic[S[left]];
        auto ub = std::upper_bound(d.begin(), d.end(), left);
        int64_t u = (ub == d.end()) ? 0 : ub - d.begin();
        auto lb = std::lower_bound(d.begin(), d.end(), right);
        int64_t l = (lb == d.end()) ? N : lb - d.begin();
        ans += right - left - (lb - ub);
        if (left == right)
        {
            ++right;
        }
    }

    std::cout << ans;
    return 0;
}