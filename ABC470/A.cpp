#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"

void AtcoderSolveHelper::Solve()
{
    int64_t N;
    In() >> N;

    for (int i = 1; i <= N; ++i)
    {
        if (i % 3 == 0)
        {
            Out() << "Fizz" << std::endl;
        }
        else
        {
            Out() << i << std::endl;
        }
    }
    return;
}

#endif //___INCLUDED_MAIN___