#include <iostream>
#include <vector>

int main()
{
    size_t N;
    std::cin >> N;
    std::vector<int64_t> A(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> A[i];
    }
    int right = 0;
    size_t ans = 0;
    auto f = [&](int l, int r) -> bool
    {
        if (r - l < 2)
        {
            return true;
        }
        if (A[r] - A[r - 1] == A[r - 1] - A[r - 2])
        {
            return true;
        }
        return false;
    };
    for (int left = 0; left < N; ++left)
    {
        while (right < N && f(left, right))
        {
            right++;
        }
        ans += right - left;
        if (left == right)
        {
            ++right;
        }
    }
    std::cout << ans;
    return 0;
}