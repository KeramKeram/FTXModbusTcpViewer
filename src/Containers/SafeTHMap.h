#pragma once

#include <map>
#include <mutex>
#include <vector>

namespace containers {
template<class T, class V> class SafeTHMap
{
public:
  SafeTHMap()  = default;
  ~SafeTHMap() = default;

  void add(const T &key, const V &value)
  {
    std::lock_guard<std::mutex> lk(mMutex);
    mContainer[key] = value;
  }

  void remove(T &key)
  {
    std::lock_guard<std::mutex> lk(mMutex);
    mContainer.erase(key);
  }

  V get(const T &key)
  {
    std::lock_guard<std::mutex> lk(mMutex);
    return mContainer[key];
  }

  void clear()
  {
    std::lock_guard<std::mutex> lk(mMutex);
    mContainer.clear();
  }

  std::vector<V> getAllValues()
  {
    std::lock_guard<std::mutex> lk(mMutex);
    std::vector<V> vals;
    transform(mContainer.begin(), mContainer.end(), back_inserter(vals), [](const auto &val) { return val.second; });
    return vals;
  }

private:
  std::map<T, V> mContainer;
  std::mutex mMutex;
};
}  // namespace containers