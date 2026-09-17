#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

#include "../module/BeamSearch.cpp"
#include "../module/BitManager.cpp"
#include "../module/Grid2D.cpp"
#include "../module/Helper.cpp"
#include <algorithm>
#include <chrono>
#include <functional>
#include <queue>
#include <random>
#include <stack>
#include <unordered_map>
#include <vector>

class State
{
  public:
    State()
    {
    }

    State(std::function<BitManager(int)> getWallFunc, std::function<int(int)> getCostFunc, int H, int W)
        : m_score(0), m_getWallFunc(getWallFunc), m_getCostFunc(getCostFunc), m_H(H), m_W(W), m_curY(H - 1), m_curX(0),
          m_addedHole(H), m_remainHole(120)
    {
    }

    void Expand(std::vector<State> &nextBeam)
    {
        if (IsFinished())
        {
            nextBeam.push_back(*this);
            return;
        }
        BitManager currentLine = m_getWallFunc(m_curY);
        BitManager prevHole = m_curY < m_H - 1 ? m_addedHole[m_curY + 1] : BitManager::AllFalse();

        // 今見るべき領域で一番左にある穴を検出
        int leftHole = -1;
        for (int x = m_curX; x < m_W; ++x)
        {
            if (currentLine.Get(x) || prevHole.Get(x))
            {
                leftHole = x;
                break;
            }
        }

        // もう塞ぐべき穴がない
        if (leftHole == -1)
        {
            --m_curY;
            m_curX = 0;
            currentLine = m_curY >= 0 ? m_getWallFunc(m_curY) : BitManager::AllFalse();
            nextBeam.push_back(*this);
            return;
        }

        // 同程度に効率よく穴をふさげる全ての置き方を試す
        for (int idx = 0; idx < 5; ++idx)
        {
            int l = idx * 2 + 1;
            if (leftHole + l > m_W)
            {
                continue;
            }
            State tmp(*this);
            tmp.m_score += m_getCostFunc(idx);
            tmp.m_curX = leftHole + l;
            tmp.m_addedHole[m_curY].Set(leftHole + idx, true);
            tmp.m_length.push_back(l);
            for (int x = leftHole; x < tmp.m_curX; ++x)
            {
                if (currentLine.Get(x) || prevHole.Get(x))
                {
                    --tmp.m_remainHole;
                }
            }
            ++tmp.m_remainHole;
            nextBeam.emplace_back(tmp);
        }

        //std::cerr << nextBeam.size() << std::endl;
    }

    bool IsFinished() const
    {
        return m_curY < 0;
    }

    int64_t GetScore() const
    {
        return m_score + m_remainHole * 20;
    }

    bool operator<(const State &rhs) const
    {
        return GetScore() < rhs.GetScore();
    }

    std::vector<BitManager> &RefHoles()
    {
        return m_addedHole;
    }

    std::vector<int> &RefLength()
    {
        return m_length;
    }

    void Output()
    {
        struct BRICK
        {
            int64_t x, y, l;
        };
        std::vector<BRICK> ans;
        int lenIdx = 0;
        auto &holes = RefHoles();
        auto &length = RefLength();
        for (int y = m_H - 1; y >= 0; --y)
        {
            auto &cur = holes[y];
            for (int x = 0; x < m_W; ++x)
            {
                if (cur.Get(x))
                {
                    ans.push_back(BRICK{.x = x - length[lenIdx] / 2, .y = y, .l = length[lenIdx]});
                    ++lenIdx;
                }
            }
        }
        std::cout << ans.size() << std::endl;
        for (auto &b : ans)
        {
            std::cout << b.x << " " << b.y << " " << b.l << std::endl;
        }
    }

  private:
    int64_t m_score;
    std::function<BitManager(int)> m_getWallFunc;
    std::function<int(int)> m_getCostFunc;
    int m_H, m_W;
    int m_curY, m_curX;
    std::vector<BitManager> m_addedHole;
    std::vector<int> m_length;
    int m_remainHole;
};
void AtcoderSolveHelper::Solve()
{
    auto startTime = std::chrono::system_clock::now();

    int64_t W, H, K;
    In() >> W >> H >> K;
    std::array<int64_t, 5> c;
    EachInput(c);
    std::vector<BitManager> Wall(H);
    for (int i = 0; i < K; ++i)
    {
        int64_t a, b;
        In() >> a >> b;
        Wall[b].Set(a, true);
    }

    State init([&Wall](int y) -> BitManager { return Wall[y]; }, [&c](int idx) -> int { return c[idx]; }, H, W);

    BeamSearch<State> bs(3000);
    State result = bs.SearchLesser(init);

    // 以下解答出力
    result.Output();

    return;
}

#endif //___INCLUDED_MAIN___