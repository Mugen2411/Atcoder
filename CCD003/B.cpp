#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

// #define ENABLE_MULTICASE //!< マルチケース用スイッチ：コメントを外すとマルチケースになる

/**
    @brief	Atcoderの解答を行うのに便利なクラス
 */
class AtcoderSolveHelper
{
private:
    //----------- 編集エリア -----------------------------
    /**
        @brief	実際に問題を解く関数
        @note   マルチケースの場合はケースごとに呼ばれます
     */
    void Solve()
    {
        int64_t N;
        In() >> N;
        std::vector<int64_t> L(N);
        std::vector<int64_t> R(N);
        std::vector<int64_t> orL(N);
        std::vector<int64_t> orR(N);
        for (int i = 0; i < N; ++i)
        {
            In() >> L[i] >> R[i];
            orL[i] = L[i];
            orR[i] = R[i];
            L[i] *= -1;
        }
        std::sort(L.begin(), L.end());
        std::sort(R.begin(), R.end());

        int64_t ans = 0;
        for (int i = 0; i < N; ++i)
        {
            auto l = std::lower_bound(R.begin(), R.end(), orL[i]);
            const int64_t lNum = [l, &R]() -> int64_t
            {
                if (l == R.end())
                {
                    return 0;
                }
                return l - R.begin();
            }();
            auto r = std::lower_bound(L.begin(), L.end(), -orR[i]);
            const int64_t rNum = [r, &L]() -> int64_t
            {
                if (r == L.end())
                {
                    return 0;
                }
                return r - L.begin();
            }();

            ans += N - lNum - rNum - 1;
        }

        Out() << ans / 2 << std::endl;
    }

    //----------- 以下編集の必要なし ----------------------

public:
    /**
        @brief	各種処理の起点になる窓口
     */
    void Run()
    {
        int64_t numTestCases = 1;
#ifdef ENABLE_MULTICASE
        In() >> numTestCases;
#endif
        while (numTestCases--)
        {
            Solve();
        }

        std::cout << Out().str();
    }

private:
    /**
        @brief	対象とするコンテナの各要素に入力を受け取る

        @tparam	TargetContainerType 対象とするコンテナの型
        @param[in]	targetContainer 対象とするコンテナ
     */
    template <class TargetContainerType>
    void EachInput(TargetContainerType &targetContainer)
    {
        for (auto &&target : targetContainer)
        {
            In() >> target;
        }
    }

    /**
        @brief	入力ストリームを取得

        @return 入力ストリーム
     */
    std::istream &In()
    {
        return std::cin;
    }

    /**
        @brief	出力ストリームを取得

        @return 出力ストリーム
     */
    std::stringstream &Out()
    {
        return m_outStream;
    }

    /**
        @brief	エラー出力ストリームを取得

        @return エラー出力ストリーム
     */
    std::ostream &Error()
    {
        return std::cerr;
    }

    /**
        @brief	Yesと1行出力する
     */
    void Yes()
    {
        Out() << "Yes" << std::endl;
    }

    /**
        @brief	Noと1行出力する
     */
    void No()
    {
        Out() << "No" << std::endl;
    }

    /**
        @brief	渡されたbool値に応じてYesかNoを出力する

        @param[in]	isYes Yesを出力するかどうか
     */
    void YesNo(bool isYes)
    {
        if (isYes)
        {
            Yes();
        }
        else
        {
            No();
        }
    }

private:
    std::stringstream m_outStream; //!< 出力を一時的に貯めておけるストリーム
};

/**
    @brief	エントリポイント

    @return ステータスコード(atcoderにおいては基本0)
 */
int main()
{
    AtcoderSolveHelper solver;
    solver.Run();
    return 0;
}