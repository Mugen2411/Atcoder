#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    struct elem
    {
        size_t id;
        long double prob;
    };
    size_t N;
    long double A, B;
    std::cin >> N;
    std::vector<elem> arr(N);
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> A >> B;
        A = A / (A + B);
        arr[i] = elem{i + 1, A};
    }
    std::sort(arr.begin(), arr.end(), [](const elem &lhs, const elem &rhs)
              {
        if(lhs.prob > rhs.prob)
        {
            return true;
        }
        if(lhs.prob < rhs.prob)
        {
            return false;
        }
        if(lhs.id < rhs.id)
        {
            return true;
        }
        return false; });
    for (const auto &i : arr)
    {
        std::cout << i.id << " ";
    }
}