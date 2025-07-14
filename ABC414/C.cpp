#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_set>

int main()
{
    int A;
    int64_t N;

    std::cin >> A >> N;

    // std::cout << digit;
    int64_t ans = 0;
    int64_t tmp = 0;

    std::unordered_set<int64_t> st;

    // len=今探してる総桁数 d=今見てる桁 v=d桁目とlen-d桁目の値
    auto dfs = [&](auto self, int len, int d, int v) -> void
    {
        int dL = d;
        int dR = len - d - 1;

        int64_t t = 0;

        int64_t tL = 1;
        for (int i = 0; i < dL; ++i)
        {
            tL *= 10;
        }

        t += tL;

        if (dL != dR)
        {
            int64_t tR = 1;
            for (int i = 0; i < dR; ++i)
            {
                tR *= 10;
            }

            t += tR;
        }

        tmp += t * v;

        if (d >= (len - 1) / 2)
        {
            int64_t a = tmp;
            std::vector<int> baseA;
            while (a != 0)
            {
                baseA.push_back(a % A);
                a /= A;
            }
            bool isParInA = true;
            for (int i = 1; i <= baseA.size() / 2; ++i)
            {
                if (baseA[i - 1] != baseA[baseA.size() - i])
                {
                    isParInA = false;
                }
            }
            if (isParInA && tmp <= N)
            {
                std::cerr << tmp << std::endl;
                st.insert(tmp);
            }
            tmp -= t * v;
            return;
        }

        for (int i = 0; i < 10; ++i)
        {
            if (tmp > N)
            {
                continue;
            }
            self(self, len, d + 1, i);
        }
        tmp -= t * v;
    };

    for (int d = 1; d <= 12; ++d)
    {
        for (int v = 1; v < 10; ++v)
        {
            dfs(dfs, d, 0, v);
        }
    }

    for (auto &s : st)
    {
        ans += s;
    }

    std::cout << ans << std::endl;

    return 0;
}