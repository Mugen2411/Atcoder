#include <iostream>
#include <vector>

template <typename T>
T gcd(T a, T b)
{
    if (a % b == 0)
    {
        return b;
    }
    else
    {
        return gcd(b, a % b);
    }
}

template <typename T>
T lcm(T a, T b)
{
    return (a * b) / gcd(a, b);
}

int main()
{
    size_t N, M, K;
    std::cin >> N >> M >> K;
    size_t ng = 0;
    size_t ok = std::max(N, M) * K;
    size_t mid;

    while (ok - ng > 1)
    {
        mid = (ok + ng) / 2;
        size_t numDivByN = mid / N;
        size_t numDivByM = mid / M;
        size_t numDivByLCM = mid / lcm(N, M);
        size_t tmp = numDivByN + numDivByM - 2 * numDivByLCM;
        if (tmp >= K)
        {
            ok = mid;
        }
        else
        {
            ng = mid;
        }
    }
    std::cout << ok << std::endl;
    return 0;
}