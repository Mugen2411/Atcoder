#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>

#define ENABLE_MULTICASE //!< マルチケース用スイッチ：コメントを外すとマルチケースになる

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
        int64_t N, M, K;
        In() >> N >> M >> K;

        std::string S;
        In() >> S;
        std::vector<std::unordered_set<int64_t>> graph(N);

        while (M--)
        {
            int64_t U, V;
            In() >> U >> V;
            --U, --V;
            graph[U].insert(V);
        }

        std::vector<std::vector<bool>> dp(K * 2 + 1);
        for (auto &d : dp)
        {
            d.resize(N, false);
        }

        // init
        for (int i = 0; i < N; ++i)
        {
            dp[K * 2][i] = (S[i] == 'A'); // alice win = true
        }

        for (int turn = K * 2 - 1; turn >= 0; --turn)
        {
            if (turn % 2 == 0)
            { // alice's turn
                for (int i = 0; i < N; ++i)
                {
                    bool canAliceWin = false;
                    for (auto &to : graph[i])
                    {
                        // can reach to win route by alice
                        if (dp[turn + 1][to])
                        {
                            canAliceWin = true;
                            break;
                        }
                    }
                    dp[turn][i] = canAliceWin;
                }
            }
            else
            { // bob's turn
                for (int i = 0; i < N; ++i)
                {
                    bool canAliceWin = true;
                    for (auto &to : graph[i])
                    {
                        // can reach to lose route by bob
                        if (!dp[turn + 1][to])
                        {
                            canAliceWin = false;
                            break;
                        }
                    }
                    dp[turn][i] = canAliceWin;
                }
            }
        }

        if (dp[0][0])
        {
            Out() << "Alice" << std::endl;
        }
        else
        {
            Out() << "Bob" << std::endl;
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