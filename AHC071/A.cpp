#ifndef ___INCLUDED_MAIN___
#define ___INCLUDED_MAIN___

//#define ENABLE_MULTICASE //!< マルチケース用スイッチ：マルチケースの場合はコメント解除

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

#ifndef ___INCLUDED_BEAM_SEARCH___
#define ___INCLUDED_BEAM_SEARCH___

#include <algorithm>
#include <cstdint>
#include <vector>

template <class State>
class BeamSearch
{
  public:
    //! @brief コンストラクタ
    //! @param beamWidth 保持する経過の個数
    BeamSearch(int64_t beamWidth) : m_beamWidth(beamWidth)
    {
    }

    //! @brief 解く
    //! @tparam EvalFunc スコアを評価する関数
    //! @param state 初期状態
    //! @param eval 評価関数
    //! @return 最も評価が高い最終状態
    template <class EvalFunc>
    State Solve(const State &state, EvalFunc eval)
    {
        std::vector<State> currentBeam;
        currentBeam.emplace_back(state);

        std::vector<State> nextBeam;
        while (1)
        {
            nextBeam.clear();

            // 全ての経過を1手進める
            for (auto &s : currentBeam)
            {
                s.Expand(nextBeam);
            }

            // 経過の中から評価が高い上位数手を残す
            std::partial_sort(nextBeam.begin(), nextBeam.begin() + std::min<int64_t>(m_beamWidth, nextBeam.size()),
                              nextBeam.end(), eval);
            if (nextBeam.size() > m_beamWidth)
            {
                nextBeam.resize(m_beamWidth);
            }

            // 残った状態を次に持ち越す
            std::swap(currentBeam, nextBeam);

            // 列挙されている状態が全て最後まで進んでいたら終了
            bool isAllSearched = true;
            for (auto &s : currentBeam)
            {
                if (!s.IsFinished())
                {
                    isAllSearched = false;
                    break;
                }
            }
            if (isAllSearched)
            {
                break;
            }
        }

        return currentBeam[0];
    }

    //! @brief よりスコアが大きいものを探す
    //! @param state 初期状態
    //! @return 最もスコアが高かった最終状態
    State SearchGreater(const State &state)
    {
        return Solve(state, std::greater<State>());
    }

    //! @brief よりスコアが小さいものを探す
    //! @param state 初期状態
    //! @return 最もスコアが低かった最終状態
    State SearchLesser(const State &state)
    {
        return Solve(state, std::less<State>());
    }

  private:
    int64_t m_beamWidth; //!< 次に持ち越す経過の個数
};

#endif //___INCLUDED_BEAM_SEARCH___

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
            m_remainHole = 0;
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
        return m_score + m_remainHole * 20 + m_entropy * 5;
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

  private:
    int64_t m_score;
    std::function<BitManager(int)> m_getWallFunc;
    std::function<int(int)> m_getCostFunc;
    int m_H, m_W;
    int m_curY, m_curX;
    std::vector<BitManager> m_addedHole;
    std::vector<int> m_length;
    int m_remainHole;
    int m_entropy;
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
    struct BRICK
    {
        int64_t x, y, l;
    };
    std::vector<BRICK> ans;
    int lenIdx = 0;
    auto &holes = result.RefHoles();
    auto &length = result.RefLength();
    for (int y = H - 1; y >= 0; --y)
    {
        auto &cur = holes[y];
        for (int x = 0; x < W; ++x)
        {
            if (cur.Get(x))
            {
                ans.push_back(BRICK{.x = x - length[lenIdx] / 2, .y = y, .l = length[lenIdx]});
                ++lenIdx;
            }
        }
    }
    Out() << ans.size() << std::endl;
    for (auto &b : ans)
    {
        Out() << b.x << " " << b.y << " " << b.l << std::endl;
    }

    return;
}

#endif //___INCLUDED_MAIN___