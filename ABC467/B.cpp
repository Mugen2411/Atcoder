#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"

void AtcoderSolveHelper::Solve()
{
    int64_t N;
    In() >> N;

    int64_t X = 10000, Y = 10000;
    while (N--)
    {
        int64_t A, B;
        std::string S;
        In() >> A >> B >> S;
        X -= B;
        Y -= B;

        Y += (B - A);
        if (S[0] == 't')
        {
            X += (B - A);
        }
    }
    Out() << Y - X;
    return;
}

#endif //___INCLUDED_MAIN___