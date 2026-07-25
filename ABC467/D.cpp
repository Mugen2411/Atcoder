#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>

void AtcoderSolveHelper::Solve()
{
    struct POS
    {
        int64_t X, Y;
    };
    POS pos[4];

    for (auto &&p : pos)
    {
        In() >> p.X >> p.Y;
        p.X *= 2;
        p.Y *= 2;
    }

    int order[4] = {0, 1, 2, 3};
    {
        POS pb = pos[order[0]];
        POS pe = pos[order[1]];
        POS qb = pos[order[2]];
        POS qe = pos[order[3]];

        auto _GetRotated = [](POS &src, POS &c) {
            POS al = {src.X - c.X, src.Y - c.Y};
            POS retval = {-al.Y, al.X};
            retval.X += c.X;
            retval.Y += c.Y;
            return retval;
        };

        POS pc = {(pb.X + pe.X) / 2, (pb.Y + pe.Y) / 2};
        POS pb2 = _GetRotated(pb, pc);
        POS pe2 = _GetRotated(pe, pc);
        POS qc = {(qb.X + qe.X) / 2, (qb.Y + qe.Y) / 2};
        POS qb2 = _GetRotated(qb, qc);
        POS qe2 = _GetRotated(qe, qc);

        POS pd = {pb2.X - pe2.X, pb2.Y - pe2.Y};
        POS qd = {qb2.X - qe2.X, qb2.Y - qe2.Y};

        if (pd.X * qd.Y != qd.X * pd.Y)
        {
            Yes();
            return;
        }
    }

    No();
    return;
}

#endif //___INCLUDED_MAIN___