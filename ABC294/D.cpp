#include <iostream>
#include <set>
#include <queue>

int main()
{
    size_t N, Q;
    std::cin >> N >> Q;
    size_t noCall = 1;
    std::set<size_t> called;
    for (int i = 0; i < Q; ++i)
    {
        size_t command;
        std::cin >> command;
        size_t tmp;
        switch (command)
        {
        case 1:
            tmp = noCall;
            ++noCall;
            called.insert(tmp);
            break;
        case 2:
            std::cin >> tmp;
            called.erase(tmp);
            break;
        case 3:
            std::cout << *called.begin() << std::endl;
            break;
        }
    }
}