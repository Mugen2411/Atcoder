#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int N, M;
    In() >> N >> M;

    std::vector<std::string> S(N);
    std::vector<std::string> T(M);
    EachInput(S);
    EachInput(T);

    std::vector<int> ans(N, 0);

    for (int i = 0; i < M; ++i)
    {
        std::vector<int> near;
        std::vector<int> tmp;
        for (int j = 0; j < N; ++j)
        {
            if (S[j].size() != T[i].size())
            {
                continue;
            }

            int diff = 0;
            for (int k = 0; k < S[j].size(); ++k)
            {
                if (S[j][k] != T[i][k])
                {
                    ++diff;
                }
            }
            if (diff == 0)
            {
                tmp.push_back(j);
                break;
            }
            else if (diff == 1)
            {
                near.push_back(j);
            }
        }

        if (!tmp.empty())
        {
            ++ans[tmp[0]];
        }
        else if (near.size() == 1)
        {
            ++ans[near[0]];
        }
    }
    for (auto &a : ans)
    {
        Out() << a << std::endl;
    }
    return;
}

#endif //___INCLUDED_MAIN___