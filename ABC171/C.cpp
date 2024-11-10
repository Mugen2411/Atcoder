#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    size_t N;
    std::cin >> N;
    --N;
    size_t cur = 26;
    int cnt = 1;
    while (1)
    {
        if (N < cur)
        {
            break;
        }

        N -= cur;
        cur *= 26;
        ++cnt;
    }
    std::vector<int> ans(cnt);
    for (int i = 0; i < cnt; ++i)
    {
        ans[i] = N % 26;
        N /= 26;
    }
    std::reverse(ans.begin(), ans.end());
    for (const auto &c : ans)
    {
        std::cout << static_cast<char>(c + 'a');
    }
    return 0;
}
