#include <string>
#include <iostream>
#include <cmath>
#include <vector>

int main()
{
    std::string S, T;
    std::cin >> S;
    std::cin >> T;
    size_t sLength = S.size();
    size_t tLength = T.size();
    for (int i = 2; i <= (sLength / tLength) + (0 != sLength % tLength); ++i)
    {
        if (i == sLength)
        {
            break;
        }
        std::vector<std::string> str((sLength / i) + (0 != sLength % i));
        for (int j = 0; j < sLength; ++j)
        {
            str[j / i] += S[j];
        }

        for (int k = 0; k < i; ++k)
        {
            size_t sameLength = 0;
            for (int j = 0; j < str.size(); ++j)
            {
                if (str[j].size() <= k)
                {
                    break;
                }
                if (str[j][k] == T[j])
                {
                    sameLength++;
                }
            }
            if (sameLength == tLength)
            {
                std::cout << "Yes";
                return 0;
            }
        }
    }
    std::cout << "No";
    return 0;
}