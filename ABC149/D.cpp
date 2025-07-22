#include <iostream>
#include <string>
#include <sstream>
#include <vector>

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
        int64_t N, K;
        int64_t R, S, P;
        In() >> N >> K >> R >> S >> P;
        std::string T;
        In() >> T;

        int64_t ans = 0;

        auto func = [&](int64_t offset)
        {
            std::vector<std::vector<int64_t>> dp(3);
            for (auto &d : dp)
            {
                if (N % K <= offset)
                {
                    d.resize(N / K);
                }
                else
                {
                    d.resize(N / K + 1);
                }
            }
            switch (T[offset])
            {
            case 'r':
            {
                dp[0][0] = P;
            }
            break;
            case 's':
            {
                dp[1][0] = R;
            }
            break;
            case 'p':
            {
                dp[2][0] = S;
            }
            break;
            }
            for (int r = 1; r < dp[0].size(); ++r)
            {
                switch (T[offset + K * r])
                {
                case 'r':
                {
                    dp[0][r] = std::max(dp[1][r - 1] + P, dp[2][r - 1] + P);
                    dp[1][r] = std::max(dp[0][r - 1], dp[2][r - 1]);
                    dp[2][r] = std::max(dp[0][r - 1], dp[1][r - 1]);
                }
                break;
                case 's':
                {
                    dp[0][r] = std::max(dp[1][r - 1], dp[2][r - 1]);
                    dp[1][r] = std::max(dp[0][r - 1] + R, dp[2][r - 1] + R);
                    dp[2][r] = std::max(dp[0][r - 1], dp[1][r - 1]);
                }
                break;
                case 'p':
                {
                    dp[0][r] = std::max(dp[1][r - 1], dp[2][r - 1]);
                    dp[1][r] = std::max(dp[0][r - 1], dp[2][r - 1]);
                    dp[2][r] = std::max(dp[0][r - 1] + S, dp[1][r - 1] + S);
                }
                break;
                }
            }

            ans += std::max(dp[0].back(), std::max(dp[1].back(), dp[2].back()));
        };

        for (int offset = 0; offset < K; ++offset)
        {
            func(offset);
        }

        Out() << ans;
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