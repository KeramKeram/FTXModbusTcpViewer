#pragma once

#include <map>
#include <mutex>

namespace containers {
    template<class T, class V>
    class SafeTHMap {
    public:
        SafeTHMap() = default;
        ~SafeTHMap() = default;

        void add(T &key, V &value) {
            std::lock_guard<std::mutex> lk(mMutex);
            mContainer[key] = value;
        }

        void remove(T &key) {
            std::lock_guard<std::mutex> lk(mMutex);
            mContainer.erase(key);
        }

        V get(T &key) {
            std::lock_guard<std::mutex> lk(mMutex);
            return mContainer[key];
        }

    private:
        std::map<T, V> mContainer;
        std::mutex mMutex;
    };
}// namespace containers