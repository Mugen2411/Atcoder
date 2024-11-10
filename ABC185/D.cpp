#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main()
{
    size_t N, M;
    std::cin >> N >> M;
    long long left = 0;
    std::vector<long long> space;
    std::vector<long long> A(M);
    long long tmp, diff;
    for (size_t i = 0; i < M; ++i)
    {
        std::cin >> A[i];
    }
    std::sort(A.begin(), A.end());
    for (size_t i = 0; i < M; ++i)
    {
        tmp = A[i];
        diff = tmp - left - 1;
        if (diff != 0)
        {
            space.push_back(diff);
        }
        left = tmp;
    }
    if (left != N)
    {
        space.push_back(N - left);
    }
    if (space.size() == 0)
    {
        std::cout << 0;
        return 0;
    }
    std::sort(space.begin(), space.end());
    long long m = space[0];
    size_t ans = 0;
    for (int i = 0; i < space.size(); ++i)
    {
        ans += space[i] / m;
        if (space[i] % m != 0)
        {
            ++ans;
        }
    }
    std::cout << ans;
    return 0;
}