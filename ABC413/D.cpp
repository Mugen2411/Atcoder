#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        int N;
        std::cin >> N;
        std::vector<int64_t> A(N);
        std::unordered_map<int64_t, std::pair<int64_t, int64_t>> dict;
        bool hasNegative = false;
        for (auto &&a : A)
        {
            std::cin >> a;
            if (a < 0)
            {
                ++dict[std::abs(a)].first;
                hasNegative = true;
            }
            else
            {
                ++dict[std::abs(a)].second;
            }
        }

        if (A.size() <= 2)
        {
            std::cout << "Yes" << std::endl;
            continue;
        }
        if (dict.size() == 1)
        {
            auto top = dict.begin();
            if ((top->second.first) == 0 || (top->second.second) == 0 || std::abs((top->second.first) - (top->second.second)) <= 1)
            {
                std::cout << "Yes" << std::endl;
                continue;
            }
            else
            {
                std::cout << "No" << std::endl;
                continue;
            }
        }
        std::sort(A.begin(), A.end(), [](const int64_t &lhs, const int64_t &rhs)
                  { return std::abs(lhs) < std::abs(rhs); });

        bool isValid = true;
        std::unordered_map<int64_t, int64_t> mult;
        for (int i = 1; i < N - 1; ++i)
        {
            if (A[i - 1] * A[i + 1] != A[i] * A[i])
            {
                isValid = false;
                break;
            }
            else
            {
                ++mult[A[i] * A[i]];
            }
        }
        if (isValid)
        {
            std::cout << "Yes" << std::endl;
        }
        else
        {
            std::cout << "No" << std::endl;
        }
    }
    return 0;
}