#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

#define DP_SIZE 250010
int64_t dp[510][DP_SIZE] = {0};

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
        int N;
        In() >> N;

        struct PARTS
        {
            int64_t W;
            int64_t H;
            int64_t B;
            int64_t diff;     //!< 体から頭に移った時に増減する嬉しさ
            long double cost; //!< この重さを頭に動かす効率
        };

        int64_t ans = 0;
        int64_t init = 0;
        int64_t buf = 0;
        std::vector<PARTS> P;
        for (int i = 0; i < N; ++i)
        {
            int64_t W, H, B;
            In() >> W >> H >> B;
            P.push_back({W, H, B, H - B, static_cast<long double>(H - B) / W});
            buf += W;
            init += B;
        }

        std::sort(P.begin(), P.end(), [](const PARTS &lhs, const PARTS &rhs)
                  { return lhs.cost > rhs.cost; });

        for (int i = 1; i <= N; ++i)
        {
            for (int w = 1; w < DP_SIZE; ++w)
            {
                if (w >= P[i - 1].W * 2)
                {
                    dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - P[i - 1].W * 2] + P[i - 1].diff);
                }
                else
                {
                    dp[i][w] = dp[i - 1][w];
                }
            }
        }
        Out() << dp[N][buf] + init;
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