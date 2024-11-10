#include <iostream>
#include <string>

int main()
{
    std::string S, T;
    std::cin >> S >> T;
    if (S != "AtCoder")
    {
        std::cout << "No";
        return 0;
    }
    if (T != "Land")
    {
        std::cout << "No";
        return 0;
    }
    std::cout << "Yes";
    return 0;
}