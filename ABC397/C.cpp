#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
    std::unordered_map<int64_t, int64_t> left;
    std::unordered_map<int64_t, int64_t> right;
    size_t N;
    std::cin >> N;
    std::vector<int64_t> A(N);
    for (auto &&a : A)
    {
        std::cin >> a;
        ++right[a];
    }

    size_t ans = 0;
    for (size_t i = 0; i < N; ++i)
    {
        ans = std::max(ans, left.size() + right.size());
        int64_t cur = A[i];
        ++left[cur];
        --right[cur];
        if (right[cur] == 0)
        {
            right.erase(cur);
        }
    }
    std::cout << ans;
    return 0;
}