#include <iostream>
#include <sstream>
#include <stack>
#include <string>
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
        int64_t N;
        In() >> N;

        std::vector<std::vector<int64_t>> graph(N);
        for (int64_t i = 0; i < N - 1; ++i)
        {
            int64_t u, v;
            In() >> u >> v;
            --u, --v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        int64_t MX = 1e10;
        std::vector<int64_t> cost(N, MX);
        std::vector<bool> searched(N, false);

        auto dfs = [&](auto self, int64_t cur) -> int64_t {
            if (cost[cur] != MX)
            {
                return cost[cur];
            }
            if (graph[cur].size() == 1)
            {
                return cost[cur] = 1;
            }
            searched[cur] = true;
            int64_t c = 1;
            for (auto &e : graph[cur])
            {
                if (searched[e])
                {
                    continue;
                }
                c += self(self, e);
            }
            return cost[cur] = c;
        };

        dfs(dfs, 0);

        int64_t mx = 0;
        int64_t sum = 0;
        for (auto &e : graph[0])
        {
            sum += cost[e];
            mx = std::max(mx, cost[e]);
        }
        int64_t ans = sum - mx;

        Out() << ans + 1;
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