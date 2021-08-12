#include "util.h"
#include "log.h"
#include "fiber.h"

#include <execinfo.h>

namespace rainbow {
// 定义日志指针
rainbow::Logger::ptr g_logger = RAINBOW_LOG_NAME("system");

pid_t GetThreadId() {
    return syscall(SYS_gettid);
}

uint32_t GetFiberId() {
    return rainbow::Fiber::GetFiberId();
}

void Backtrace(std::vector<std::string>& bt, int size, int skip) {
    void** array = (void**)malloc((sizeof(void*) * size));
    // 返回真实的层数
    size_t s = ::backtrace(array, size);

    // 获取栈中的内容
    char** strings = backtrace_symbols(array, s);
    if(strings == NULL) {
        RAINBOW_LOG_ERROR(g_logger) << "backtrace_synbols error";
        return ;
    }

    // 把每一层真的内容放进去
    for (size_t i = skip; i < s; ++i) {
        bt.push_back(strings[i]);
    }
    free(strings);
    free(array);
}

/**
 * 将栈中的内容序列化输出到 stringstream 中
 * prefix 支持在每一个栈的前面加入换行、空格等
 */
std::string BacktraceToString(const std::string& prefix, int size, int skip) {
    std::vector<std::string> bt;
    Backtrace(bt, size, skip);
    std::stringstream ss;
    for(size_t i = 0; i < bt.size(); ++i) {
        ss << prefix << bt[i] << std::endl;
    }
    return ss.str(); 
}

}
