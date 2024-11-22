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
    std::unordered_set<int> set;
    auto f = [&](int left, int right) -> bool
    {
        if (A[right] == A[right - 1] && set.count(A[right]) == 0)
        {
            return true;
        }
        return false;
    };
    int64_t ans = 0;
    int right = 0;
    for (int left = 0; left < N; left += 2)
    {
        while (right < N && f(left, right))
        {
            set.insert(A[right]);
            right += 2;
        }
        int64_t size = (right - left);

        ans = std::max(ans, size);
        if (left == right)
        {
            right += 2;
        }
        else
        {
            set.erase(A[left]);
        }
    }
    set.clear();
    right = 1;
    for (int left = 1; left < N; left += 2)
    {
        while (right < N && f(left, right))
        {
            set.insert(A[right]);
            right += 2;
        }
        int64_t size = (right - left);

        ans = std::max(ans, size);
        if (left == right)
        {
            right += 2;
        }
        else
        {
            set.erase(A[left]);
        }
    }
    std::cout << ans;
    return 0;
}