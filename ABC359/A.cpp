#include <iostream>
#include <string>

int main()
{
    std::string tmp;
    std::size_t N;
    std::cin >> N;
    size_t ans = 0;
    for (size_t i = 0; i < N; ++i)
    {
        std::cin >> tmp;
        if (tmp == "Takahashi")
        {
            ++ans;
        }
    }
    std::cout << ans << std::endl;
    return 0;
}