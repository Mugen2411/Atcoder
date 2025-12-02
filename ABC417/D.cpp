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
        std::vector<int64_t> P(N);
        std::vector<int64_t> A(N);
        std::vector<int64_t> B(N);

        for (int i = 0; i < N; ++i)
        {
            In() >> P[i] >> A[i] >> B[i];
        }

        constexpr int64_t MAX_BORDER = 500;
        std::vector<int64_t[MAX_BORDER * 2 + 1]> dp(N);

        for (int i = 0; i <= MAX_BORDER * 2; ++i)
        {
            dp[N - 1][i] = (i <= P[N - 1]) ? i + A[N - 1] : std::max<int64_t>(0ll, i - B[N - 1]);
        }

        for (int64_t n = N - 2; n >= 0; --n)
        {
            for (int64_t i = 0; i <= MAX_BORDER * 2; ++i)
            {
                dp[n][i] = (i <= P[n]) ? dp[n + 1][i + A[n]] : std::max<int64_t>(0ll, dp[n + 1][std::max<int64_t>(0ll, i - B[n])]);
            }
        }

        std::vector<int64_t> over(N + 1);
        over[0] = MAX_BORDER;
        for (int i = 1; i <= N; ++i)
        {
            over[i] = over[i - 1] + B[i - 1];
        }
        std::vector<int64_t> negative(N + 1);
        negative[0] = 0;
        for (int i = 1; i <= N; ++i)
        {
            negative[i] = negative[i - 1] - B[i - 1];
        }

        int64_t Q;
        In() >> Q;
        while (Q--)
        {
            int64_t X;
            In() >> X;
            int64_t offset = std::lower_bound(over.begin(), over.end(), X) - over.begin();
            if (offset >= N)
            {
                Out() << X + negative.back() << std::endl;
                continue;
            }
            X += negative[offset];
            Out() << dp[offset][X] << std::endl;
        }
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