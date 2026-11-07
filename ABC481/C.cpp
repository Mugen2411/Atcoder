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
    int64_t Q;
    In() >> Q;

    std::unordered_map<std::string, int64_t> dict;
    while (Q--)
    {
        std::string s;
        In() >> s;
        if (dict.count(s) == 0)
        {
            dict[s] = dict.size() + 1;
        }
        Out() << dict[s] << std::endl;
    }
    return;
}

#endif //___INCLUDED_MAIN___