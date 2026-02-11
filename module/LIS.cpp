#ifndef ___INCLUDED_LIS___
#define ___INCLUDED_LIS___

#include <limits>
#include <vector>

//! @brief 最長増加部分列
class LIS
{
  public:
    //! 最長増加部分列の長さを取得する
    //! @tparam 型
    template <class T>
    static int64_t GetLength(const std::vector<T> &src)
    {
        const int64_t INF = std::numeric_limits<T>::max();
        std::vector<T> dp(src.size(), INF);

        for (int i = 0; i < src.size(); ++i)
        {
            auto itr = std::lower_bound(dp.begin(), dp.end(), src[i]);
            *itr = std::min(*itr, src[i]);
        }
        auto pos = std::lower_bound(dp.begin(), dp.end(), INF);
        return std::distance(dp.begin(), pos);
    }
};

#endif //___INCLUDED_LIS___