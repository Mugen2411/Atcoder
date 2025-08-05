#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <set>

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
        int64_t N, M, X, Y;
        In() >> N >> M >> X >> Y;
        --X, --Y;

        std::vector<std::set<int64_t>> graph(N);

        while (M--)
        {
            int64_t U, V;
            In() >> U >> V;
            --U, --V;
            graph[U].insert(V);
            graph[V].insert(U);
        }

        std::vector<std::vector<int64_t>> ans;
        std::vector<int64_t> searched(N);
        auto dfs = [&](auto self, int64_t cur, std::vector<int64_t> route) -> void
        {
            if (!ans.empty())
            {
                return;
            }
            if (cur == Y)
            {
                route.push_back(cur);
                ans.push_back(route);
                return;
            }
            for (auto e : graph[cur])
            {
                if (searched[e] == 0)
                {
                    searched[e] = 1;
                    auto next = route;
                    next.push_back(cur);
                    self(self, e, next);
                }
            }
        };
        searched[X] = 1;
        dfs(dfs, X, std::vector<int64_t>());

        // std::sort(ans.begin(), ans.end());

        for (auto &rt : ans[0])
        {
            Out() << rt + 1 << " ";
        }
        Out() << std::endl;
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