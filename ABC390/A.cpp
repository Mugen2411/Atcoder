#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> A(5);
    for (int i = 0; i < 5; ++i)
    {
        std::cin >> A[i];
    }
    int wrong = 0;
    for (int i = 0; i < 5; ++i)
    {
        if (A[i] != i + 1)
        {
            ++wrong;
            A[i] = -1;
        }
    }
    auto itr = std::unique(A.begin(), A.end());
    A.erase(itr, A.end());
    if (A.size() == 4)
    {
        std::cout << "Yes";
    }
    else
    {
        std::cout << "No";
    }
    return 0;
}