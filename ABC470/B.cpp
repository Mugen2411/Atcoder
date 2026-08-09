#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"

#include <vector>
void AtcoderSolveHelper::Solve()
{
    int64_t N;
    In() >> N;
    std::vector<int64_t> C(N);
    std::vector<int64_t> cnt(N);
    EachInput(C);
    for (auto c : C)
    {
        ++cnt[c - 1];
    }
    int64_t mx = 0;
    for (auto c : cnt)
    {
        mx = std::max<int64_t>(mx, c);
    }
    Out() << N - mx;
    return;
}

#endif //___INCLUDED_MAIN___