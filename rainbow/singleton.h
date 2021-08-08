#ifndef __RAINBOW_SINGLETON_H_
#define __RAINBOW_SINGLETON_H_

#include <memory>

namespace rainbow {

template<class T, class X = void, int N = 0>
class Singleton {
public:
    static T* GetInstance() {
        static T v;
        return &v;
    }

};

template<class T, class X = void, int N = 0>
class Singletonptr {
public:
    static std::shared_ptr<T> GetInstance() {
        static std::shared_ptr<T> v(new T);
        return v;
    }

};

}

#endif
