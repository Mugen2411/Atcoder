#include <iostream>
#include <string>

int main()
{
    std::string P;
    int L;

    std::cin >> P >> L;
    if (P.size() >= L)
    {
        std::cout << "Yes";
        return 0;
    }
    else
    {
        std::cout << "No";
        return 0;
    }

    return 0;
}