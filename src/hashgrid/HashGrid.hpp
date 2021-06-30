#ifndef HASHGRID_HPP_
#define HASHGRID_HPP_

#include "robin_hood.h"
#include <array>
#include <cmath>
#include <vector>

template <typename T> class HashGrid
{
  public:

    HashGrid()
      : mCellSize(50)
      , mInvCellSize(1.f / static_cast<float>(mCellSize))
    {}

    HashGrid(const std::size_t cellSize)
      : mCellSize(cellSize)
      , mInvCellSize(1.f / static_cast<float>(cellSize))
    {}

    ~HashGrid()
    {}

    void add(const float x, const float y, T* data)
    {
      mHashMap[index(x, y, mInvCellSize)].emplace_back(data);
    }

    std::vector<T*> get(const float x, const float y)
    {
      const int64_t SZ = static_cast<int64_t>(mCellSize);
      std::vector<int64_t> indexes;
      for(int64_t cx = -SZ; cx <= SZ; cx+= SZ)
      {
	for(int64_t cy = -SZ; cy <= SZ; cy+= SZ)
	{
	  const float ix = x + cx;
	  const float iy = y + cy;
	  indexes.emplace_back(index(ix, iy, mInvCellSize));
	}
      }

      std::vector<T*> res;
      for(auto& idx : indexes)
      {
	if(mHashMap.find(idx) != mHashMap.end())
	{
	  res.insert(res.end(), mHashMap[idx].begin(), mHashMap[idx].end());
	}
      }
      return res;
    }

    void clear()
    {
      mHashMap.clear();
    }

    const std::size_t getCellSize() const
    {
      return mCellSize;
    }

  private:
    const std::size_t mCellSize;
    const float mInvCellSize;
    static constexpr int64_t prime1 = 73856093;
    static constexpr int64_t prime2 = 19349663;
    static constexpr int64_t prime3 = 734687;
    static constexpr int64_t prime4 = 234713;

    typedef robin_hood::unordered_map<int64_t, std::vector<T*>> HashMap;
    HashMap mHashMap;

    static constexpr int64_t index(const float x, const float y, const float invCellSize)
    {
      const int ix = std::floor(x * invCellSize);
      const int iy = std::floor(y * invCellSize) * prime2;
      //return (ix  * prime1) ^ (iy  * prime2);
      return int64_t(((ix + prime3) * prime1) ^ ((iy + prime4) * prime2));
    }
};



#endif /* HASHGRID_HPP_ */
