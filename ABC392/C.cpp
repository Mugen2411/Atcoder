#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int64_t N;
    std::cin >> N;
    std::vector<int64_t> P(N);
    std::vector<int64_t> Q(N);
    for (int i = 0; i < N; ++i)
    {
        std::cin >> P[i];
    }
    for (int i = 0; i < N; ++i)
    {
        std::cin >> Q[i];
    }
    struct Person
    {
        int64_t P, Q;
    };
    std::vector<Person> p;
    for (int i = 0; i < N; ++i)
    {
        p.push_back({P[i], Q[i]});
    }
    std::sort(p.begin(), p.end(), [](const Person &lhs, const Person &rhs)
              { return lhs.Q < rhs.Q; });
    for (int i = 0; i < N; ++i)
    {
        std::cout << Q[p[i].P - 1] << " ";
    }
    return 0;
}