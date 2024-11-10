#include <iostream>
#include <string>

int main()
{
    std::string S;
    std::cin >> S;
    size_t l = S.size();
    if (S[l - 3] == 's' && S[l - 2] == 'a' && S[l - 1] == 'n')
    {
        std::cout << "Yes";
    }
    else
    {
        std::cout << "No";
    }
    return 0;
}