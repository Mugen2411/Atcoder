#ifndef ___INCLUDED_TRIE_TREE___
#define ___INCLUDED_TRIE_TREE___

#include <map>
#include <memory>
#include <vector>

//! @brief Trie木クラス
//! @tparam T 格納するデータの型(比較演算子が実装されている)
template <class T>
class TrieTree
{
  public:
    //! @brief 木のノード
    struct NODE
    {
        std::map<T, NODE *> Children; //!< 子のノードたち
        T Value;                      //!< 自分の値
        int64_t NumCommon = 0;        //!< このデータを通過するデータの個数
    };

  public:
    //! @brief デフォルトコンストラクタ
    TrieTree()
    {
        m_createdNodes.push_back(std::make_unique<NODE>()); // ルートノードを0番に追加
    }

    //! @brief ルートノードを取得
    //! @return ルートノード
    NODE *GetRootNode() const
    {
        return m_createdNodes[0].get();
    }

    //! @brief pNodeの子としてvalueを追加する
    //! @param value 追加する値
    //! @param pNode 追加する元のノード
    //! @return 追加された結果の末端ノード
    NODE *Insert(const T &value, NODE *pNode)
    {
        if (pNode->Children.count(value) == 0)
        {
            auto p = std::make_unique<NODE>();
            p->Value = value;
            pNode->Children[value] = p.get();
            m_createdNodes.push_back(std::move(p));
            return m_createdNodes.back().get();
        }

        NODE *pRet = pNode->Children[value];
        ++pRet->NumCommon;
        return pRet;
    }

    //! @brief シーケンスとしてデータを追加する
    //! @tparam Source データ源の型
    //! @param src データ源
    //! @return 追加されたノード
    template <class Source>
    NODE *Insert(const Source &src)
    {
        NODE *pCur = GetRootNode();
        for (auto &s : src)
        {
            pCur = Insert(s, pCur);
        }
        return pCur;
    }

    //! @brief 木をDFSしながら何らかの処理をする
    //! @tparam Func 処理本体の型(引数はNODE*型)
    //! @param f 処理本体
    template <class Func>
    void Dfs(Func f)
    {
        auto _Dfs = [this, f](auto self, NODE *pNode) -> void {
            for (auto &n : pNode->Children)
            {
                f(n.second);
                self(self, n.second);
            }
        };

        _Dfs(_Dfs, GetRootNode());
    }

  private:
    std::vector<std::unique_ptr<NODE>> m_createdNodes; //!< 作成されたノードのプール
};

#endif //___INCLUDED_TRIE_TREE___