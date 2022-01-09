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
        }

        V get(T &key) {
        }

    private:
        std::map<T, V> mContainer;
        std::mutex mMutex;
    };
}// namespace containers