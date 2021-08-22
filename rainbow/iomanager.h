#ifndef __RAINBOW_IOMANAGER_H__
#define __RAINBOW_IOMANAGER_H__

#include "scheduler.h"
#include "timer.h"

namespace rainbow {

/*! class IOManager
 *  brief Brief class description
 *
 *  Detailed description
 */
class IOManager : public Scheduler, public TimerManager{
public:
    typedef std::shared_ptr<IOManager> ptr;
    typedef RWMutex RWMutexType;

    enum Event {
        NONE    = 0x0,
        READ    = 0x1,  // EPOLLIN
        WRITE   = 0x4,  // EPOLLOUT
    };

private:
    struct FdContext {
        typedef Mutex MutexType;
        struct EventContext {
            Scheduler* scheduler = nullptr;           // 事件执行的 scheduler
            std::shared_ptr<Fiber> fiber;   // 事件协程
            std::function<void()> cb;       // 事件的回调函数
        };

        EventContext& getContext(Event event);
        void resetContext(EventContext& ctx);
        void triggerEvent(Event event);

        EventContext read;      // 读事件
        EventContext write;     // 写事件
        int fd = 0;             // 事件关联的句柄
        Event events = NONE;    // 已经注册的事件
        MutexType mutex;
    };

public:
    IOManager(size_t threads = 1, bool use_caller = true, const std::string& name = "");
    ~IOManager();

    // 1 success, 0 retry, -1 error
    int addEvent(int fd, Event event, std::function<void()> cb = nullptr);
    bool delEvent(int fd, Event event);
    bool cancelEvent(int fd, Event event);

    bool cancelAll(int fd);

    static IOManager* GetThis();

protected:
    // scheduler 中的三个虚方法
    void tickle() override;
    // 决定协程调度模块是否应该终止
    bool stopping() override;
    // 没有事件要执行的话就会陷入到 epoll_wait 中
    void idle() override;
    void onTimerInsertedAtFront() override;

    void contextResize(size_t size);
    bool stopping(uint64_t& timeout);

private:
    int m_epfd = 0;
    int m_tickleFds[2];

    std::atomic<size_t> m_pendingEventCount = {0};
    RWMutexType m_mutex;
    std::vector<FdContext*> m_fdContexts;
};

}

#endif /* ifndef __RAINBOW_IOMANAGER_H__ */
