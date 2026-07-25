#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"

void AtcoderSolveHelper::Solve()
{
    int64_t H, W;
    In() >> H >> W;

    YesNo(W * 100 * 100 >= 25 * H * H);
    return;
}

#endif //___INCLUDED_MAIN___