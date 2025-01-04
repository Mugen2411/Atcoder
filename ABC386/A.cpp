#include <iostream>
#include <set>

int main()
{
    std::set<int> s;
    for (int i = 0; i < 4; ++i)
    {
        int tmp;
        std::cin >> tmp;
        s.insert(tmp);
    }
    if (s.size() == 2)
    {
        std::cout << "Yes";
        return 0;
    }
    else
    {
        std::cout << "No";
    }
    return 0;
}