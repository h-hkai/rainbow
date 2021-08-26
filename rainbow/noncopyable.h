#ifndef __RAINBOW_NONCOPYABLR_H__
#define __RAINBOW_NONCOPYABLR_H__

namespace rainbow {

class Noncopyable {
public:
    Noncopyable() = default;
    ~Noncopyable() = default;
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;
};

}

#endif /* ifndef __RAINBOW_NONCOPYABLR_H__ */
