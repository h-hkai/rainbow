#ifndef __RAINBOW_LOG_H
#define __RAINBOW_LOG_H

#include "singleton.h"

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

#define RAINBOW_LOG_ROOT() rainbow::LoggerMgr::GetInstance()->getRoot();

namespace rainbow {

class Logger;


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
};

// 日志事件
class LogEvent {
   public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char* file, 
            int32_t m_line, uint32_t elapse, uint32_t thread_id, uint32_t fiber_id, uint64_t time);
    ~LogEvent() {}

    std::shared_ptr<Logger> getLogger() const {  return m_logger; }
    LogLevel::Level getLevel() const { return m_level; }

    const char* getFileName() const { return m_file; }
    int32_t getLine() const { return m_line; }
    uint32_t getElapse() const { return m_elapse; }
    uint32_t getThreadId() const { return m_threadId; }
    uint32_t getFiberId() const { return m_fiberId; }
    uint32_t getTime() const { return m_time; }
    std::string getContent() const { return m_ss.str(); }
    
    std::stringstream& getSS() { return m_ss; }
    void format(const char* fmt, ...);
    void format(const char* fmt, va_list al);
   
   private:
    const char* m_file = nullptr;  // 文件名
    int32_t m_line = 0;            // 行号
    uint32_t m_elapse = 0;         // 程序启动开始到现在的毫秒数
    uint32_t m_threadId = 0;       // 线程id
    uint32_t m_fiberId = 0;        // 协程id
    uint64_t m_time;               // 时间戳
    std::stringstream m_ss;
    std::shared_ptr<Logger> m_logger;
    LogLevel::Level m_level;
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
    typedef std::shared_ptr<LogFormatter> ptr;
    LogFormatter(const std::string& pattern);

    std::string format(std::shared_ptr<Logger> ptr, LogLevel::Level level,
                       LogEvent::ptr event);
    std::ostream& format(std::ostream& ofs, std::shared_ptr<Logger> ptr, LogLevel::Level level, LogEvent::ptr event);

   public:
    class FormatItem {
       public:
        FormatItem(const std::string& fmt = ""){};
        virtual ~FormatItem() {}
        virtual void format(std::ostream& os, std::shared_ptr<Logger> logger,
                            LogLevel::Level level, LogEvent::ptr event) = 0;
        // 注意这里的指针类型是FormatItem类型的指针
        typedef std::shared_ptr<FormatItem> ptr;
    };

    void init();

   private:
    std::string m_pattern;
    std::vector<FormatItem::ptr> m_items;
};

// 日志输出到目的地（控制台、文件）
class LogAppender {
   public:
    typedef std::shared_ptr<LogAppender> ptr;
    LogAppender();
    virtual ~LogAppender() {}
    // 纯虚函数，子类必须实现该方法
    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level,
                     LogEvent::ptr event) = 0;
    // 按照给定的格式序列化输出
    void setFormatter(LogFormatter::ptr val) { m_formatter = val; }
    LogFormatter::ptr getFormatter() const { return m_formatter; }

    LogLevel::Level getLevel() { return m_level; }
    void setLevel(const LogLevel::Level& level);

   protected:
    LogLevel::Level m_level;
    LogFormatter::ptr m_formatter;
};

// 日志器
class Logger : public std::enable_shared_from_this<Logger> {
   public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string& name = "root");

    void log(LogLevel::Level level, LogEvent::ptr event);

    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);

    LogLevel::Level getLevel() const { return m_level; }
    void setAppender(LogLevel::Level val) { m_level = val; }

    const std::string getName() const { return this->m_name; }

   private:
    std::string m_name = "root";       // 日志名称
    LogLevel::Level m_level;  // 满足日志级别的日志才会被输出
    std::list<LogAppender::ptr> m_appenders;  // Appender集合
    LogFormatter::ptr m_formatter;
};

// 输出到控制台的Appender
class StdoutLogAppender : public LogAppender {
   public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    virtual void log(Logger::ptr logger, LogLevel::Level level,
                     LogEvent::ptr event) override;
};

// 定义输出到文件的Appender
class FileLogAppender : public LogAppender {
   public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    virtual void log(Logger::ptr logger, LogLevel::Level level,
                     LogEvent::ptr event) override;
    FileLogAppender(const std::string& filename);
    // 重新打开文件，如果文件打开成功则返回true
    bool reopen();

   private:
    std::string m_filename;
    std::ofstream m_filestream;
};

class LoggerManager {
public:
    LoggerManager();
    Logger::ptr getLogger(const std::string& name);

    void init();
    Logger::ptr getRoot() const { return m_root; }

private:
    std::map<std::string, Logger::ptr> m_loggers;
    Logger::ptr m_root;
};

typedef rainbow::Singleton<LoggerManager> LoggerMgr;

}  // namespace rainbow

#endif
