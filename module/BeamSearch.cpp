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

            currentBeam[0].Output();
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