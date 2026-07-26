#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include "../module/PrefixSum.cpp"

void AtcoderSolveHelper::Solve()
{
    size_t N;
    In() >> N;

    Grid3D<int64_t> A(N, N, N, 0);
    In() >> A;
    PrefixSum<int64_t> pres(A);

    int64_t Q;
    In() >> Q;
    while (Q--)
    {
        size_t Lx, Rx, Ly, Ry, Lz, Rz;
        std::cin >> Lx >> Rx >> Ly >> Ry >> Lz >> Rz;

        int64_t ans = pres.GetSum(Rz, Lz - 1, Ry, Ly - 1, Rx, Lx - 1);

        Out() << ans << std::endl;
    }

    return;
}

#endif //___INCLUDED_MAIN___