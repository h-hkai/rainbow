#ifndef __RAINBOW_LOG_H
#define __RAINBOW_LOG_H

#include "singleton.h"
#include "util.h"
#include "thread.h"

#include <stdio.h>
#include <stdint.h>
#include <memory>
#include <stdarg.h>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <map>

#define RAINBOW_LOG_LEVEL(logger, level) \
    if (logger->getLevel() <= level) \
        rainbow::LogEventWrap(rainbow::LogEvent::ptr(new rainbow::LogEvent(logger, level, __FILE__, __LINE__, 0, rainbow::GetThreadId(), rainbow::GetFiberId(), time(0)))).getSS()

#define RAINBOW_LOG_DEBUG(logger) RAINBOW_LOG_LEVEL(logger, rainbow::LogLevel::DEBUG)
#define RAINBOW_LOG_INFO(logger) RAINBOW_LOG_LEVEL(logger, rainbow::LogLevel::INFO)
#define RAINBOW_LOG_WARN(logger) RAINBOW_LOG_LEVEL(logger, rainbow::LogLevel::WARN)
#define RAINBOW_LOG_ERROR(logger) RAINBOW_LOG_LEVEL(logger, rainbow::LogLevel::ERROR)
#define RAINBOW_LOG_FATAL(logger) RAINBOW_LOG_LEVEL(logger, rainbow::LogLevel::FATAL)

#define RAINBOW_LOG_FMT_LEVEL(logger, level, fmt, ...) \
    if (logger->getLevel() <= level) \
        rainbow::LogEventWrap(rainbow::LogEvent::ptr(new rainbow::LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, rainbow::GetThreadId(), \
                        rainbow::GetFiberId(), time(0)))).getEvent()->format(fmt, __VA_ARGS__)

#define RAINBOW_LOG_FMT_DEBUG(logger, fmt, ...) RAINBOW_LOG_FMT_LEVEL(logger, rainbow::LogLevel::DEBUG, fmt, __VA_ARGS__)
#define RAINBOW_LOG_FMT_INFO(logger, fmt, ...) RAINBOW_LOG_FMT_LEVEL(logger, rainbow::LogLevel::INFO, fmt, __VA_ARGS__)
#define RAINBOW_LOG_FMT_WARN(logger, fmt, ...) RAINBOW_LOG_FMT_LEVEL(logger, rainbow::LogLevel::WARN, fmt, __VA_ARGS__)
#define RAINBOW_LOG_FMT_ERROR(logger, fmt, ...) RAINBOW_LOG_FMT_LEVEL(logger, rainbow::LogLevel::ERROR, fmt, __VA_ARGS__)
#define RAINBOW_LOG_FMT_FATAL(logger, fmt, ...) RAINBOW_LOG_FMT_LEVEL(logger, rainbow::LogLevel::FATAL, fmt, __VA_ARGS__)

// 采用宏定义的方式获取日志器（root）
#define RAINBOW_LOG_ROOT() rainbow::LoggerMgr::GetInstance()->getRoot()
#define RAINBOW_LOG_NAME(name) rainbow::LoggerMgr::GetInstance()->getLogger(name)

namespace rainbow {

class Logger;
class LoggerManager;

// 日志级别
class LogLevel {
   public:
    enum Level {
        UNKNOW = 0,
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };

    static const char* ToString(LogLevel::Level level);
    static LogLevel::Level FromString(const std::string& str);
};

// 日志事件
class LogEvent {
   public:
    // 指向日志事件的指针
    typedef std::shared_ptr<LogEvent> ptr;
    /*
     * 构造函数
     * 传入 Logger 指针，可以将该日志事件写入到对应的 Logger 中
     */
    LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char* file, 
            int32_t m_line, uint32_t elapse, uint32_t thread_id, uint32_t fiber_id, uint64_t time);
    ~LogEvent() {}

    // 获取该日志事件所对应的 Logger 类
    std::shared_ptr<Logger> getLogger() const {  return m_logger; }
    
    // 获取日志级别
    LogLevel::Level getLevel() const { return m_level; }
    
    // 获取文件名
    const char* getFileName() const { return m_file; }
    
    // 获取行号
    int32_t getLine() const { return m_line; }
    
    // 获取运行的时间
    uint32_t getElapse() const { return m_elapse; }
    
    // 获取线程 id
    uint32_t getThreadId() const { return m_threadId; }
    
    // 获取协程 id
    uint32_t getFiberId() const { return m_fiberId; }
    
    // 获取当前时间
    uint32_t getTime() const { return m_time; }
    
    // 获取日志内容
    std::string getContent() const { return m_ss.str(); }
    
    // 以 stringstream 的形式获取日志内容
    std::stringstream& getSS() { return m_ss; }
    
    // 将日志内容进行格式化
    void format(const char* fmt, ...);
    void format(const char* fmt, va_list al);
   
   private:
    const char* m_file = nullptr;  // 文件名
    int32_t m_line = 0;            // 行号
    uint32_t m_elapse = 0;         // 程序启动开始到现在的毫秒数
    uint32_t m_threadId = 0;       // 线程id
    uint32_t m_fiberId = 0;        // 协程id
    uint64_t m_time;               // 时间戳
    std::stringstream m_ss;             // 日志流
    std::shared_ptr<Logger> m_logger;   // 指向 Logger 类的指针
    LogLevel::Level m_level;            // 该日志事件的级别
};

class LogEventWrap {
public:
    LogEventWrap(LogEvent::ptr e);
    ~LogEventWrap();
    std::stringstream& getSS();
    LogEvent::ptr getEvent() const { return m_event; }

private:
    LogEvent::ptr m_event;
};

// 日志格式器
class LogFormatter {
   public:
    // 指向该类的指针
    typedef std::shared_ptr<LogFormatter> ptr;
    
    // 日志格式
    LogFormatter(const std::string& pattern);
    
    // 对日志进行解析，并返回格式化之后的string
    std::string format(std::shared_ptr<Logger> ptr, LogLevel::Level level,
                       LogEvent::ptr event);
    std::ostream& format(std::ostream& ofs, std::shared_ptr<Logger> ptr, LogLevel::Level level, LogEvent::ptr event);

   public:
    // 日志格式解析单元类
    class FormatItem {
       public:
        FormatItem(const std::string& fmt = ""){};
        virtual ~FormatItem() {}
        // 将解析后的日志输出到 os 流中
        virtual void format(std::ostream& os, std::shared_ptr<Logger> logger,
                            LogLevel::Level level, LogEvent::ptr event) = 0;
        // 注意这里的指针类型是FormatItem类型的指针
        typedef std::shared_ptr<FormatItem> ptr;
    };

    /**
     * @brief 初始化，解析日志模板
     */
    void init();

    bool isError() const {
        return m_error;
    }

    const std::string getPattern() const { return m_pattern; }

   private:
    // 日志格式
    std::string m_pattern;
    // 根据日志格式将对应的解析器指针存放在该数组中
    std::vector<FormatItem::ptr> m_items;
    bool m_error = false;
};

// 日志输出到目的地（控制台、文件）
class LogAppender {
friend class Logger;
public:
    typedef std::shared_ptr<LogAppender> ptr;
    typedef Spinlock MutexType;
    LogAppender();
    virtual ~LogAppender() {}
    // 纯虚函数，子类必须实现该方法
    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level,
                     LogEvent::ptr event) = 0;

    virtual std::string toYamlString() = 0;

    // 按照给定的格式序列化输出
    void setFormatter(LogFormatter::ptr val);
    
    // 获取日志格式
    LogFormatter::ptr getFormatter(); 

    LogLevel::Level getLevel() const { return m_level; }
    void setLevel(const LogLevel::Level& level);

   protected:
    // LogAppender 的日志级别
    LogLevel::Level m_level = LogLevel::DEBUG;
    bool m_hasFormatter = false;
    // LoggerAppender 的日志格式
    LogFormatter::ptr m_formatter;

    MutexType m_mutex;
};

// 日志器
class Logger : public std::enable_shared_from_this<Logger> {
friend class LoggerManager;

public:
    typedef std::shared_ptr<Logger> ptr;
    typedef Spinlock MutexType;

    Logger(const std::string& name = "root");
    
    // 只有满足日直级别的日志才会被输出
    void log(LogLevel::Level level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    void clearAppenders();

    LogLevel::Level getLevel() const { return m_level; }
    void setLevel(LogLevel::Level level) { m_level = level; }

    void setAppender(LogLevel::Level val) { m_level = val; }

    const std::string getName() const { return this->m_name; }
    
    void setFormatter(LogFormatter::ptr val);
    void setFormatter(const std::string& val);

    LogFormatter::ptr getFormatter();

    std::string toYamlString();

   private:
    std::string m_name;       // 日志名称
    LogLevel::Level m_level;  // 日志器的级别
    MutexType m_mutex;
    std::list<LogAppender::ptr> m_appenders;  // Appender集合
    LogFormatter::ptr m_formatter;            // 日志格式
    Logger::ptr m_root;
};

// 输出到控制台的Appender
class StdoutLogAppender : public LogAppender {
   public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(Logger::ptr logger, LogLevel::Level level,
                     LogEvent::ptr event) override;

    std::string toYamlString() override;
};

// 定义输出到文件的Appender
class FileLogAppender : public LogAppender {
   public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    void log(Logger::ptr logger, LogLevel::Level level,
                     LogEvent::ptr event) override;
    FileLogAppender(const std::string& filename);
    // 重新打开文件，如果文件打开成功则返回true
    bool reopen();

    std::string toYamlString() override;

   private:
    std::string m_filename;
    std::ofstream m_filestream;
    uint64_t m_lastTime = 0;
};

// 管理所有的日志器
class LoggerManager {
public:
    typedef Spinlock MutexType;
    LoggerManager();
    Logger::ptr getLogger(const std::string& name);

    void init();
    Logger::ptr getRoot() const { return m_root; }

    std::string toYamlString();

private:
    MutexType m_mutex;
    // 通过日志器的名字获取日志器
    std::map<std::string, Logger::ptr> m_loggers;
    Logger::ptr m_root;
};

/**
 * 日志器管理类，单例模式
 */
typedef rainbow::Singleton<LoggerManager> LoggerMgr;

}  // namespace rainbow

#endif
