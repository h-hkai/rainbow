#ifndef __RAINBOW_TIMER_H__
#define __RAINBOW_TIMER_H__

#include <memory>
#include <set>
#include <vector>

#include "thread.h"

namespace rainbow {

class TimerManager;

class Timer : public std::enable_shared_from_this<Timer> {
friend class TimerManager;

public:
    typedef std::shared_ptr<Timer> ptr;

    bool cancel();
    bool refresh();
    bool reset(uint64_t ms, bool from_now);

private:
    // 构造函数
    Timer(uint64_t ms, std::function<void()> cb,
          bool recurring, TimerManager* manager);
    Timer(uint64_t next);

private:
    // 循环定时器
    bool m_recurring = false;
    // 执行周期
    uint64_t m_ms = 0; 
    // 精确的时间
    uint64_t m_next = 0;
    std::function<void()> m_cb;
    TimerManager* m_manager = nullptr;

private:
    struct Comparator {
        bool operator() (const Timer::ptr& lhs, const Timer::ptr& rhs) const;
    }; /* optional variable list */;
};

class TimerManager {
friend class Timer;

public:
    typedef RWMutex RWMutexType;

    TimerManager();
    virtual ~TimerManager();

    Timer::ptr addTimer(uint64_t ms, std::function<void()> cb
                        ,bool recurring = false);
    Timer::ptr addConditionTimer(uint64_t ms, std::function<void()> cb
                        ,std::weak_ptr<void> weak_cond
                        ,bool recurring = false);
    uint64_t getNextTimer();
    void listExpiredCb(std::vector<std::function<void()>>& cbs);
protected:
    virtual void onTimerInsertedAtFront() = 0;
    void addTimer(Timer::ptr val, RWMutexType::WriteLock& lock);
    bool hasTimer();
private:
    bool detectClockRollover(uint64_t now_ms);
private:
    RWMutexType m_mutex;
    std::set<Timer::ptr, Timer::Comparator> m_timers;
    bool m_tickled = false;
    uint64_t m_previouseTime = 0;
};

}

#endif /* ifndef __RAINBOW_TIMER_H__ */
