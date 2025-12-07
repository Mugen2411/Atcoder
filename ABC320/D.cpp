#include <iostream>
#include <limits>
#include <sstream>
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
        struct Coord
        {
            int64_t x, y;

            bool operator==(const Coord &rhs) const
            {
                return x == rhs.x && y == rhs.y;
            }
            bool operator!=(const Coord &rhs) const
            {
                return !(operator==(rhs));
            }
        };
        const Coord INVALID = {std::numeric_limits<int64_t>::max(), std::numeric_limits<int64_t>::max()};

        struct Edge
        {
            Coord dist;
            int64_t to;
        };

        int64_t N, M;
        In() >> N >> M;

        std::vector<std::vector<Edge>> graph(N);
        std::vector<Coord> absPos(N, INVALID);

        while (M--)
        {
            int64_t A, B;
            Coord d = INVALID;

            In() >> A >> B >> d.x >> d.y;
            --A, --B;
            graph[A].push_back(Edge{d, B});
            graph[B].push_back(Edge{Coord{-d.x, -d.y}, A});
        }

        auto dfs = [&](auto self, int64_t cur, Coord curPos) {
            if (absPos[cur] != INVALID)
            {
                return;
            }
            absPos[cur] = curPos;
            for (auto &e : graph[cur])
            {
                self(self, e.to, Coord{curPos.x + e.dist.x, curPos.y + e.dist.y});
            }
        };
        dfs(dfs, 0, Coord{0, 0});

        for (auto &p : absPos)
        {
            if (p == INVALID)
            {
                Out() << "undecidable" << std::endl;
            }
            else
            {
                Out() << p.x << " " << p.y << std::endl;
            }
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