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
        rainbow::LogEventWrap(rainbow::LogEvent::ptr(new rainbow::LogEvent(logger, level, __FILE__, __LINE__, 0, rainbow::GetThreadId(), rainbow::GetFiberId(), time(0), rainbow::Thread::GetName()))).getSS()

#define RAINBOW_LOG_DEBUG(logger) RAINBOW_LOG_LEVEL(logger, rainbow::LogLevel::DEBUG)
#define RAINBOW_LOG_INFO(logger) RAINBOW_LOG_LEVEL(logger, rainbow::LogLevel::INFO)
#define RAINBOW_LOG_WARN(logger) RAINBOW_LOG_LEVEL(logger, rainbow::LogLevel::WARN)
#define RAINBOW_LOG_ERROR(logger) RAINBOW_LOG_LEVEL(logger, rainbow::LogLevel::ERROR)
#define RAINBOW_LOG_FATAL(logger) RAINBOW_LOG_LEVEL(logger, rainbow::LogLevel::FATAL)

#define RAINBOW_LOG_FMT_LEVEL(logger, level, fmt, ...) \
    if (logger->getLevel() <= level) \
        rainbow::LogEventWrap(rainbow::LogEvent::ptr(new rainbow::LogEvent(logger, level, \
                        __FILE__, __LINE__, 0, rainbow::GetThreadId(), \
                        rainbow::GetFiberId(), time(0), rainbow::Thread::GetName()))).getEvent()->format(fmt, __VA_ARGS__)

#define RAINBOW_LOG_FMT_DEBUG(logger, fmt, ...) RAINBOW_LOG_FMT_LEVEL(logger, rainbow::LogLevel::DEBUG, fmt, __VA_ARGS__)
#define RAINBOW_LOG_FMT_INFO(logger, fmt, ...) RAINBOW_LOG_FMT_LEVEL(logger, rainbow::LogLevel::INFO, fmt, __VA_ARGS__)
#define RAINBOW_LOG_FMT_WARN(logger, fmt, ...) RAINBOW_LOG_FMT_LEVEL(logger, rainbow::LogLevel::WARN, fmt, __VA_ARGS__)
#define RAINBOW_LOG_FMT_ERROR(logger, fmt, ...) RAINBOW_LOG_FMT_LEVEL(logger, rainbow::LogLevel::ERROR, fmt, __VA_ARGS__)
#define RAINBOW_LOG_FMT_FATAL(logger, fmt, ...) RAINBOW_LOG_FMT_LEVEL(logger, rainbow::LogLevel::FATAL, fmt, __VA_ARGS__)

// ??????????????????????????????????????????root???
#define RAINBOW_LOG_ROOT() rainbow::LoggerMgr::GetInstance()->getRoot()
#define RAINBOW_LOG_NAME(name) rainbow::LoggerMgr::GetInstance()->getLogger(name)

namespace rainbow {

class Logger;
class LoggerManager;

// ????????????
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

// ????????????
class LogEvent {
   public:
    // ???????????????????????????
    typedef std::shared_ptr<LogEvent> ptr;
    /*
     * ????????????
     * ?????? Logger ??????????????????????????????????????????????????? Logger ???
     */
    LogEvent(std::shared_ptr<Logger> logger, LogLevel::Level level, const char* file, 
            int32_t m_line, uint32_t elapse, uint32_t thread_id, uint32_t fiber_id, 
            uint64_t time, const std::string& thread_name);
    ~LogEvent() {}

    // ????????????????????????????????? Logger ???
    std::shared_ptr<Logger> getLogger() const {  return m_logger; }
    
    // ??????????????????
    LogLevel::Level getLevel() const { return m_level; }
    
    // ???????????????
    const char* getFileName() const { return m_file; }
    
    // ????????????
    int32_t getLine() const { return m_line; }
    
    // ?????????????????????
    uint32_t getElapse() const { return m_elapse; }
    
    // ???????????? id
    uint32_t getThreadId() const { return m_threadId; }
    
    // ???????????? id
    uint32_t getFiberId() const { return m_fiberId; }
    
    // ??????????????????
    uint32_t getTime() const { return m_time; }

    const std::string& getThreadName() { return m_threadName; }
    
    // ??????????????????
    std::string getContent() const { return m_ss.str(); }
    
    // ??? stringstream ???????????????????????????
    std::stringstream& getSS() { return m_ss; }
    
    // ??????????????????????????????
    void format(const char* fmt, ...);
    void format(const char* fmt, va_list al);
   
   private:
    const char* m_file = nullptr;  // ?????????
    int32_t m_line = 0;            // ??????
    uint32_t m_elapse = 0;         // ???????????????????????????????????????
    uint32_t m_threadId = 0;       // ??????id
    uint32_t m_fiberId = 0;        // ??????id
    uint64_t m_time;               // ?????????
    std::string m_threadName;
    std::stringstream m_ss;             // ?????????
    std::shared_ptr<Logger> m_logger;   // ?????? Logger ????????????
    LogLevel::Level m_level;            // ????????????????????????
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

// ???????????????
class LogFormatter {
   public:
    // ?????????????????????
    typedef std::shared_ptr<LogFormatter> ptr;
    
    // ????????????
    LogFormatter(const std::string& pattern);
    
    // ???????????????????????????????????????????????????string
    std::string format(std::shared_ptr<Logger> ptr, LogLevel::Level level,
                       LogEvent::ptr event);
    std::ostream& format(std::ostream& ofs, std::shared_ptr<Logger> ptr, LogLevel::Level level, LogEvent::ptr event);

   public:
    // ???????????????????????????
    class FormatItem {
       public:
        FormatItem(const std::string& fmt = ""){};
        virtual ~FormatItem() {}
        // ?????????????????????????????? os ??????
        virtual void format(std::ostream& os, std::shared_ptr<Logger> logger,
                            LogLevel::Level level, LogEvent::ptr event) = 0;
        // ??????????????????????????????FormatItem???????????????
        typedef std::shared_ptr<FormatItem> ptr;
    };

    /**
     * @brief ??????????????????????????????
     */
    void init();

    bool isError() const {
        return m_error;
    }

    const std::string getPattern() const { return m_pattern; }

   private:
    // ????????????
    std::string m_pattern;
    // ??????????????????????????????????????????????????????????????????
    std::vector<FormatItem::ptr> m_items;
    bool m_error = false;
};

// ????????????????????????????????????????????????
class LogAppender {
friend class Logger;
public:
    typedef std::shared_ptr<LogAppender> ptr;
    typedef Spinlock MutexType;
    LogAppender();
    virtual ~LogAppender() {}
    // ??????????????????????????????????????????
    virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level,
                     LogEvent::ptr event) = 0;

    virtual std::string toYamlString() = 0;

    // ????????????????????????????????????
    void setFormatter(LogFormatter::ptr val);
    
    // ??????????????????
    LogFormatter::ptr getFormatter(); 

    LogLevel::Level getLevel() const { return m_level; }
    void setLevel(const LogLevel::Level& level);

   protected:
    // LogAppender ???????????????
    LogLevel::Level m_level = LogLevel::DEBUG;
    bool m_hasFormatter = false;
    // LoggerAppender ???????????????
    LogFormatter::ptr m_formatter;

    MutexType m_mutex;
};

// ?????????
class Logger : public std::enable_shared_from_this<Logger> {
friend class LoggerManager;

public:
    typedef std::shared_ptr<Logger> ptr;
    typedef Spinlock MutexType;

    Logger(const std::string& name = "root");
    
    // ????????????????????????????????????????????????
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
    std::string m_name;       // ????????????
    LogLevel::Level m_level;  // ??????????????????
    MutexType m_mutex;
    std::list<LogAppender::ptr> m_appenders;  // Appender??????
    LogFormatter::ptr m_formatter;            // ????????????
    Logger::ptr m_root;
};

// ?????????????????????Appender
class StdoutLogAppender : public LogAppender {
   public:
    typedef std::shared_ptr<StdoutLogAppender> ptr;
    void log(Logger::ptr logger, LogLevel::Level level,
                     LogEvent::ptr event) override;

    std::string toYamlString() override;
};

// ????????????????????????Appender
class FileLogAppender : public LogAppender {
   public:
    typedef std::shared_ptr<FileLogAppender> ptr;
    void log(Logger::ptr logger, LogLevel::Level level,
                     LogEvent::ptr event) override;
    FileLogAppender(const std::string& filename);
    // ??????????????????????????????????????????????????????true
    bool reopen();

    std::string toYamlString() override;

   private:
    std::string m_filename;
    std::ofstream m_filestream;
    uint64_t m_lastTime = 0;
};

// ????????????????????????
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
    // ???????????????????????????????????????
    std::map<std::string, Logger::ptr> m_loggers;
    Logger::ptr m_root;
};

/**
 * ?????????????????????????????????
 */
typedef rainbow::Singleton<LoggerManager> LoggerMgr;

}  // namespace rainbow

#endif
