#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/Helper.cpp"
#include <algorithm>
#include <iomanip>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

#include "../module/PrefixSum.cpp"

void AtcoderSolveHelper::Solve()
{
    int64_t N, Q;
    In() >> N >> Q;

    struct POS
    {
        long double X, Y;
    };
    std::vector<POS> pos(N);

    for (auto &&p : pos)
    {
        In() >> p.X >> p.Y;
    }

    pos.push_back(pos.front());

    std::vector<long double> cx;
    for (int i = 0; i < N; ++i)
    {
        cx.push_back((pos[i].X + pos[i + 1].X) * (pos[i].X * pos[i + 1].Y - pos[i + 1].X * pos[i].Y));
    }
    std::vector<long double> cy;
    for (int i = 0; i < N; ++i)
    {
        cy.push_back((pos[i].Y + pos[i + 1].Y) * (pos[i].X * pos[i + 1].Y - pos[i + 1].X * pos[i].Y));
    }

    std::vector<long double> solid;
    for (int i = 0; i < N; ++i)
    {
        solid.push_back(pos[i].X * pos[i + 1].Y - pos[i + 1].X * pos[i].Y);
    }
    PrefixSum<long double> xPres(cx.begin(), cx.end());
    PrefixSum<long double> yPres(cy.begin(), cy.end());
    PrefixSum<long double> sPres(solid.begin(), solid.end());

    while (Q--)
    {
        int64_t u, v;
        In() >> u >> v;
        --u, --v;

        if (u < v)
        {
            long double cs = (pos[v].X * pos[u].Y - pos[u].X * pos[v].Y);
            long double s = sPres.GetSum(v, u);
            s += cs;
            s *= 3;
            long double x = xPres.GetSum(v, u);
            long double y = yPres.GetSum(v, u);

            long double dx = (pos[v].X + pos[u].X) * (pos[v].X * pos[u].Y - pos[u].X * pos[v].Y);
            long double dy = (pos[v].Y + pos[u].Y) * (pos[v].X * pos[u].Y - pos[u].X * pos[v].Y);
            x += dx;
            y += dy;

            Out() << std::setprecision(10) << std::fixed << x / s << " " << y / s << std::endl;
        }
        else
        {
            long double cs = (pos[u].X * pos[v].Y - pos[v].X * pos[u].Y);
            long double s = sPres.GetSum(v, 0) + sPres.GetSum(N, u);
            s -= cs;
            s *= 3;
            long double x = xPres.GetSum(v, 0) + xPres.GetSum(N, u);
            long double y = yPres.GetSum(v, 0) + yPres.GetSum(N, u);

            long double dx = (pos[v].X + pos[u].X) * (pos[v].X * pos[u].Y - pos[u].X * pos[v].Y);
            long double dy = (pos[v].Y + pos[u].Y) * (pos[v].X * pos[u].Y - pos[u].X * pos[v].Y);
            x += dx;
            y += dy;

            Out() << std::setprecision(10) << std::fixed << x / s << " " << y / s << std::endl;
        }
    }
}

#endif //___INCLUDED_MAIN___