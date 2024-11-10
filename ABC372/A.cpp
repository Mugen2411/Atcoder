#include <string>
#include <iostream>

int main()
{
    std::string S;
    std::cin >> S;
    for (auto &c : S)
    {
        if (c != '.')
        {
            std::cout << c;
        }
    }
    return 0;
}