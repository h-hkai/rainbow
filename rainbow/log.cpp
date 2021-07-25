#include "log.h"

#include <functional>
#include <map>
#include <time.h>
#include <stdio.h>


namespace rainbow {

class TabFormatItem : public LogFormatter::FormatItem {
    public:
     TabFormatItem(const std::string& str = "") {}
     void format(std::ostream& os, std::shared_ptr<Logger> logger,
     LogLevel::Level level, LogEvent::ptr event) override {
         os << "\t";
     }
};

class MessageFormatItem : public LogFormatter::FormatItem {
   public:
    MessageFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger,
                LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getContent();
    }
};

class LevelFormatItem : public LogFormatter::FormatItem {
   public:
    LevelFormatItem(const std::string str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger,
                LogLevel::Level level, LogEvent::ptr event) override {
        os << LogLevel::ToString(level);
    }
};

class ElapseFormatItem : public LogFormatter::FormatItem {
   public:
    ElapseFormatItem(const std::string str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger,
                LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getElapse();
    }
};

class ThreadIdFormatItem : public LogFormatter::FormatItem {
   public:
    ThreadIdFormatItem(const std::string str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger,
                LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getThreadId();
    }
};

class FiberIdFormatItem : public LogFormatter::FormatItem {
   public:
    FiberIdFormatItem(const std::string str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger,
                LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getFiberId();
    }
};

class DateTimeFormatItem : public LogFormatter::FormatItem {
   public:
    DateTimeFormatItem(const std::string& format = "%Y-%m-%d %H:%M:%s")
        : m_format(format) {
            if (m_format.empty()) {
                m_format = "%Y-%m-%d %H:%M:%S";
            }
        }
    void format(std::ostream& os, std::shared_ptr<Logger> logger,
                LogLevel::Level level, LogEvent::ptr event) override {
        time_t rawtime = event->getTime();
        struct tm timeinfo;
        timeinfo = *localtime(&rawtime);
        char buf[64];
        strftime(buf, sizeof(buf), m_format.c_str(), &timeinfo);
        os << buf;
    }

   private:
    std::string m_format;
};

class FileNameFormatItem : public LogFormatter::FormatItem {
   public:
    FileNameFormatItem(const std::string str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger,
                LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getFileName();
    }
};

class LineFormatItem : public LogFormatter::FormatItem {
   public:
    LineFormatItem(const std::string str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger,
                LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getLine();
    }
};

class NewLineFormatItem : public LogFormatter::FormatItem {
   public:
    NewLineFormatItem(const std::string str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger,
                LogLevel::Level level, LogEvent::ptr event) override {
        os << std::endl;
    }
};

class StringFormatItem : public LogFormatter::FormatItem {
   public:
    StringFormatItem(const std::string& str) : m_string(str) {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger,
                LogLevel::Level level, LogEvent::ptr event) override {
        os << m_string;
    }
    std::string getString() const { return m_string; }

   private:
    std::string m_string;
};

class NameFormatItem : public LogFormatter::FormatItem {
   public:
    NameFormatItem(const std::string str = "") {}
    void format(std::ostream& os, std::shared_ptr<Logger> logger,
                LogLevel::Level level, LogEvent::ptr event) override {
        os << event->getLogger()->getName();
    }
};

const char* LogLevel::ToString(LogLevel::Level level) {
    switch (level) {
#define XX(name)         \
    case LogLevel::name: \
        return #name;    \
        break;
        XX(UNKNOW);
        XX(DEBUG);
        XX(INFO);
        XX(WARN);
        XX(ERROR);
        XX(FATAL);
#undef XX
        default:
            return "UNKNOW";
            break;
    }
}

LogEvent::LogEvent(const std::shared_ptr<Logger> logger, LogLevel::Level level, const char* file, 
        int32_t line, uint32_t elapse, uint32_t thread_id, uint32_t fiber_id, uint64_t time)
    : m_file(file),
      m_line(line),
      m_elapse(elapse),
      m_threadId(thread_id),
      m_fiberId(fiber_id),
      m_time(time),
      m_logger(logger),
      m_level(level) {}

void LogEvent::format(const char* fmt, ...) {
    va_list al;
    va_start(al, fmt);
    format(fmt, al);
    va_end(al);
}

void LogEvent::format(const char* fmt, va_list al) {
    char* buf = nullptr;
    int len = vasprintf(&buf, fmt, al);
    if (len != -1) {
        m_ss << std::string(buf, len);
        free(buf);
    }
}


LogEventWrap::LogEventWrap(LogEvent::ptr e) : m_event(e) {

}

LogEventWrap::~LogEventWrap() {
    m_event->getLogger()->log(m_event->getLevel(), m_event);
}

std::stringstream& LogEventWrap::getSS() {
    return m_event->getSS();
}



Logger::Logger(const std::string& name)
    : m_name(name), m_level(LogLevel::DEBUG) {
    m_formatter.reset(new LogFormatter("%d%T%t%T%F%T[%p]%T%c%T%f:%l%T%m%n"));
}

void Logger::addAppender(LogAppender::ptr appender) {
    // 保证每一个都有 Formatter
    if (!appender->getFormatter()) {
        appender->setFormatter(m_formatter);
    }
    m_appenders.push_back(appender);
}

void Logger::delAppender(LogAppender::ptr appender) {
    for (auto it = m_appenders.begin(); it != m_appenders.end(); ++it) {
        if (*it == appender) {
            m_appenders.erase(it);
            break;
        }
    }
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event) {
    if (level >= m_level) {
        auto self = shared_from_this();
        for (auto& it : m_appenders) {
            it->log(self, level, event);
        }
    }
}

void Logger::debug(LogEvent::ptr event) { log(LogLevel::DEBUG, event); }

void Logger::info(LogEvent::ptr event) { log(LogLevel::INFO, event); }

void Logger::warn(LogEvent::ptr event) { log(LogLevel::WARN, event); }

void Logger::error(LogEvent::ptr event) { log(LogLevel::ERROR, event); }

void Logger::fatal(LogEvent::ptr event) { log(LogLevel::FATAL, event); }

LogAppender::LogAppender() {
    m_level = LogLevel::DEBUG;
}

void LogAppender::setLevel(const LogLevel::Level& level) {
    m_level = level;
}

FileLogAppender::FileLogAppender(const std::string& name) : m_filename(name) {}

void FileLogAppender::log(std::shared_ptr<Logger> logger, LogLevel::Level level,
                          LogEvent::ptr event) {
    if (level >= m_level) {
        if (reopen()) {
            m_filestream << m_formatter->format(logger, level, event);
        }
    }
}

bool FileLogAppender::reopen() {
    if (m_filestream) {
        m_filestream.close();
    }
    m_filestream.open(m_filename);
    return (bool)m_filestream;
}

void StdoutLogAppender::log(std::shared_ptr<Logger> logger,
                            LogLevel::Level level, LogEvent::ptr event) {
    if (level >= m_level) {
        std::cout << m_formatter->format(logger, level, event);
    }
}

void LogFormatter::FormatItem::format(std::ostream& os,
                                      std::shared_ptr<Logger> logger,
                                      LogLevel::Level level,
                                      LogEvent::ptr event) {}

LogFormatter::LogFormatter(const std::string& pattern) : m_pattern(pattern) {
    init();
}

/**
 * 函数功能：对字符串 "%d{ABSOLUTE} %5p %c{1}:%L - %m%n"
 * 进行解析，将模式转换的参数与格式以及类型存入到一个tuple中。
 * type = -1 代表解析失败
 * type = 0  代表只是一个字符串用format来存储，不涉及模式转换
 * type = 1  代表模式转换解析成功
 *
 **/
void LogFormatter::init() {
    // param, str, type
    std::vector<std::tuple<std::string, std::string, int> > vec;

    size_t i = 0;
    std::string param = "", str = "";

    while (i < m_pattern.length()) {
        while (i < m_pattern.length() && m_pattern[i] != '%') {
           param = m_pattern[i++];
           vec.push_back(std::make_tuple(param, "", 1));
           while (i < m_pattern.length() && m_pattern[i] != '%') {
               str.append(1, m_pattern[i++]);
           }
           break;
        }
        if (i < m_pattern.length() && str != "") {
            vec.push_back(std::make_tuple("", str, 0));
            str = "";
        }
        i++;
    }

    static std::map<std::string, std::function<LogFormatter::FormatItem::ptr(const std::string& str)> > s_format_items = {
#define XX(str, C) \
    {#str, [](const std::string& fmt) { return LogFormatter::FormatItem::ptr(new C(fmt)); }} 

        XX(m, MessageFormatItem),  
	    XX(p, LevelFormatItem),
        XX(r, ElapseFormatItem),   
	    XX(c, NameFormatItem),
        XX(t, ThreadIdFormatItem), 
 	    XX(n, NewLineFormatItem),
        XX(d, DateTimeFormatItem), 
	    XX(f, FileNameFormatItem),
        XX(l, LineFormatItem),
        XX(T, TabFormatItem),
        XX(F, FiberIdFormatItem),
#undef XX
        };

    for (auto& i : vec) {
        if (std::get<2>(i) == 0) {
            StringFormatItem* sfmt = new StringFormatItem(std::get<1>(i));
            m_items.push_back(FormatItem::ptr(new StringFormatItem(sfmt->getString())));
        } else {
            auto it = s_format_items.find(std::get<0>(i));
            if (it == s_format_items.end()) {
                m_items.push_back(FormatItem::ptr(new StringFormatItem(
                    "<<error_format %" + std::get<0>(i) + ">>")));
            } else {
                m_items.push_back(it->second(std::get<1>(i)));
            }
        }
    }
}

// 将日志信息输出到流中
std::string LogFormatter::format(std::shared_ptr<Logger> logger,
                                 LogLevel::Level level, LogEvent::ptr event) {
    std::stringstream ss;
    for (auto it : m_items) {
        it->format(ss, logger, level, event);
    }
    return ss.str();
}

LoggerManager::LoggerManager() {
    m_root.reset(new Logger);
    m_root->addAppender(LogAppender::ptr(new StdoutLogAppender));

}

Logger::ptr LoggerManager::getLogger(const std::string& name) {
    auto it = m_loggers.find(name);
    return it == m_loggers.end() ? m_root : it->second;
}

}  // namespace rainbow
