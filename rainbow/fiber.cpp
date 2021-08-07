#include "fiber.h"
#include "config.h"
#include "macro.h"

#include <atomic>

namespace rainbow {

static std::atomic<uint64_t> s_fiber_id {0};
static std::atomic<uint64_t> s_fiber_cout {0};

static thread_local Fiber* t_fiber = nullptr;
// 主协程
static thread_local std::shared_ptr<Fiber::ptr> t_threadFiber = nullptr;

static ConfigVar<uint32_t>::ptr g_fiber_stack_size = 
    Config::Lookup<uint32_t>("fiber.stack_size", 1024 * 1024, "fiber stack size");

class MallocStackAllocator {
public:
    static void* Alloc(size_t size) {
        return malloc(size);
    }

    static void Dealloc(void* vp, size_t size) {
        return free(vp);
    }
};

using StackAllocator = MallocStackAllocator;

Fiber::Fiber() {
    m_state = EXEC;
    SetThis(this);

    if(getcontext(&m_ctx)) {
        RAINBOW_ASSERT(false, "getcontest");
    }

    ++s_fiber_count;
}

Fiber::Fiber(std::function<void()> cb, size_t stacksize) 
    :m_id(++s_fiber_id)
     ,m_cb(cb) {
    ++s_fiber_count;
    m_stacksize = stacksize ? stacksize : g_fiber_stack_size->getValue();

    m_stack = StackAllocator::Alloc(m_stacksize);

    if(getcontext(&m_ctx)) {
        RAINBOW_ASSERT(false, "getcontest");
    }

    m_ctx.uc_link = nullptr;
    m_ctx.uc_stack.ss_sp = m_stack;
    m_ctx.uc_stack.ss_size = m_stacksize;

    makecontext(&m_ctx, &Fiber::MainFunc, 0);
}

Fiber::~Fiber() {
    --s_fiber_count;
    if(m_stack) {
        RAINBOW_ASSERT(m_state == TERM || m_state == INIT);

        StackAllocator::Dealloc(m_stack, m_stacksize);
    } else {
        RAINBOW_ASSERT(!m_cb);
        RAINBOW_ASSERT(m_state == EXEC);
         
        Fiber* cur = t_fiber;
        if (cur == this) {
            SetThis(nullptr);
        }
    }
}

// 重置协程函数，并重置状态
// INIT, TERM
void Fiber::reset(std::function<void()> cb) {
    RAINBOW_ASSERT(m_stack);
    RAINBOW_ASSERT(m_state == TERM || m_state == INIT);
    m_cb = cb;
    if (getcontext(&m_ctx)) {
        RAINBOW_ASSERT2(false, "getcontext");
    }

    m_ctx.uc_link = nullptr;
    m_ctx.uc_stack.ss_sp = m_stack;
    m_ctx.uc_stack.ss_size = m_stacksize;

    makecontext(&m_ctx, &Fiber::MainFunc, 0);
    m_state = INIT;
}
// 切换到当前协程执行
void Fiber::swapIn() {
    SetThis(this);
    RAINBOW_ASSERT(m_state != EXEC);

    m_state = EXEC;
    if(swapcontext(&(*t_threadFiber)->m_ctx, &m_ctx)) {
        RAINBOW_ASSERT(false, "swapcontext");
    }
}
// 切换到后台
void Fiber::swapOut() {
    SetThis(t_threadFiber.get());

    if(swapcontext(&m_ctx, &t_threadFiber->m_ctx)) {
        RAINBOW_ASSERT(false, "swapcontext");
    }
}
// set current fiber
void SetThis(Fiber* f) {
    t_fiber = f;
}
// 返回当前协程
Fiber::ptr Fiber::GetThis() {
    if(t_fiber) {
        return t_fiber->shared_from_this();
    }

    Fiber::ptr main_fiber(new Fiber);
    RAINBOW_ASSERT(t_fiber == main_fiber.get());
    t_threadFiber = main_fiber;
    return t_fiber->shared_from_this();
}
// 协程切换到后台，并且设置为Ready状态
void Fiber::YieldToReady() {

}
// 协程切换到后台，并设置为Hold状态
static void YieldToHold();
// 总协程
static uint64_t TotalFibers();

static MainFunc();



}
