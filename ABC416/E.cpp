#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <unordered_map>

// #define ENABLE_MULTICASE //!< マルチケース用スイッチ：コメントを外すとマルチケースになる

template <typename T>
using greater_priority_queue = std::priority_queue<T, std::vector<T>, std::greater<T>>;

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
        int64_t N, M;
        In() >> N >> M;
        struct EDGE
        {
            int64_t to;
            int64_t cost;
        };
        std::vector<std::unordered_map<int64_t, int64_t>> graph(N);

        auto PushEdge = [&](int64_t from, int64_t to, int64_t cost)
        {
            if (graph[from].count(to) != 0 && graph[from][to] < cost)
            {
                return;
            }
            graph[from][to] = cost;
        };
        while (M--)
        {
            int64_t A, B, C;
            In() >> A >> B >> C;
            --A, --B;
            PushEdge(A, B, C);
            PushEdge(B, A, C);
        }

        int64_t K, T;
        In() >> K >> T;
        std::unordered_set<int64_t> airport;
        while (K--)
        {
            int64_t D;
            In() >> D;
            airport.insert(--D);
        }

        for (auto &from : airport)
        {
            for (auto &to : airport)
            {
                if (from == to)
                {
                    continue;
                }
                PushEdge(from, to, T);
            }
        }

        const int64_t INVALID = 0xffffffffffffff;
        auto search = [&](int64_t start)
        {
            std::vector<int64_t> distance(N, INVALID);
            greater_priority_queue<std::pair<int64_t, int64_t>> q;
            q.emplace((distance[start] = 0), start);

            while (!q.empty())
            {
                const long long dist = q.top().first;
                const int from = q.top().second;
                q.pop();

                if (distance[from] < dist)
                {
                    continue;
                }

                for (const auto &edge : graph[from])
                {
                    const int64_t d = (distance[from] + edge.second);

                    if (d < distance[edge.first])
                    {
                        q.emplace((distance[edge.first] = d), edge.first);
                    }
                }
            }

            int64_t ans = 0;
            for (auto d : distance)
            {
                if (d != INVALID)
                {
                    ans += d;
                }
            }
            return ans;
        };

        int64_t Q;
        In() >> Q;
        while (Q--)
        {
            int cmd;
            In() >> cmd;
            switch (cmd)
            {
            case 1:
            {
                int64_t x, y, t;
                In() >> x >> y >> t;
                --x, --y;
                PushEdge(x, y, t);
                PushEdge(y, x, t);
            }
            break;
            case 2:
            {
                int64_t x;
                In() >> x;
                --x;
                for (auto &a : airport)
                {
                    PushEdge(a, x, T);
                    PushEdge(x, a, T);
                }
                airport.insert(x);
            }
            break;
            case 3:
            {
                int64_t ans = 0;
                for (int i = 0; i < N; ++i)
                {
                    ans += search(i);
                }
                Out() << ans << std::endl;
            }
            }
        }
    }

    //----------- 以下編集の必要なし ----------------------

public:
    /**
        @brief	各種処理の起点になる窓口
     */
    void
    Run()
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