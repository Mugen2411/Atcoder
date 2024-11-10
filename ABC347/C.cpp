#include <iostream>
#include <set>

int main()
{
    size_t N, A, B;
    std::cin >> N >> A >> B;
    std::set<size_t> s;
    size_t tmp;
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> tmp;
        s.insert(tmp % (A + B));
    }
    size_t minimum = *s.begin();
    size_t maximum = *s.rbegin();
    if (maximum - minimum < A)
    {
        std::cout << "Yes" << std::endl;
        return 0;
    }

    s.erase(minimum);
    s.insert(minimum + A + B);
    minimum = *s.begin();
    maximum = *s.rbegin();
    if (maximum - minimum < A)
    {
        std::cout << "Yes";
        return 0;
    }

    std::cout << "No" << std::endl;

    return 0;
}