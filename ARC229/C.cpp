#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <cmath>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void AtcoderSolveHelper::Solve()
{
    int64_t N;
    In() >> N;

    std::vector<int64_t> A(N);
    EachInput(A);

    std::sort(A.begin(), A.end());
    std::vector<int64_t> odd;
    std::vector<int64_t> even;
    std::vector<int64_t> ans;
    int64_t first = A.back();
    A.pop_back();
    int64_t last = A.back();
    A.pop_back();

    ans.push_back(first);

    for (auto a : A)
    {
        if (a % 2)
        {
            odd.push_back(a);
        }
        else
        {
            even.push_back(a);
        }
    }

    {
        int64_t evenIdx = 0;
        int64_t oddIdx = 0;
        while (odd.size() > oddIdx && even.size() > evenIdx)
        {
            ans.push_back(even[evenIdx]);
            ++evenIdx;
            ans.push_back(odd[oddIdx]);
            ++oddIdx;
        }
        for (int i = evenIdx; i < even.size(); ++i)
        {
            ans.push_back(even[i]);
        }
        for (int i = oddIdx; i < odd.size(); ++i)
        {
            ans.push_back(odd[i]);
        }
    }
    ans.push_back(last);

    if (ans.size() != N)
    {
        int *np = NULL;
        *np = 0xDEADC0DE;
    }

    int64_t sum1 = 0;
    for (int i = 0; i < N - 1; ++i)
    {
        sum1 += (ans[i] + ans[i + 1]) / 2;
    }

    ans.clear();
    ans.push_back(first);

    {
        int64_t evenIdx = 0;
        int64_t oddIdx = 0;
        while (odd.size() > oddIdx && even.size() > evenIdx)
        {
            ans.push_back(odd[oddIdx]);
            ++oddIdx;
            ans.push_back(even[evenIdx]);
            ++evenIdx;
        }
        for (int i = evenIdx; i < even.size(); ++i)
        {
            ans.push_back(even[i]);
        }
        for (int i = oddIdx; i < odd.size(); ++i)
        {
            ans.push_back(odd[i]);
        }
    }

    ans.push_back(last);

    if (ans.size() != N)
    {
        int *np = NULL;
        *np = 0xDEADC0DE;
    }

    int64_t sum2 = 0;
    for (int i = 0; i < N - 1; ++i)
    {
        sum2 += (ans[i] + ans[i + 1]) / 2;
    }

    Out() << std::min<int64_t>(sum1, sum2) << std::endl;

    return;
}

#endif //___INCLUDED_MAIN___