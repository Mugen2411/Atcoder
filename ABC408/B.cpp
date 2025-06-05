#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    int N;
    std::cin >> N;
    std::vector<int> A(N);
    for (auto &&a : A)
    {
        std::cin >> a;
    }
    std::sort(A.begin(), A.end());
    auto end = std::unique(A.begin(), A.end());
    std::cout << end - A.begin() << std::endl;
    for (auto itr = A.begin(); itr != end; ++itr)
    {
        std::cout << *itr << " ";
    }
    return 0;
}