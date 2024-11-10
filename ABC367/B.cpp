#include <iostream>
#include <string>

int main()
{
    std::string X;
    std::cin >> X;
    while (1)
    {
        if (*X.rbegin() == '0')
        {
            X.pop_back();
        }
        else
        {
            break;
        }
        if (*X.rbegin() == '.')
        {
            X.pop_back();
            break;
        }
    }
    for (auto &c : X)
    {
        std::cout << c;
    }
    return 0;
}