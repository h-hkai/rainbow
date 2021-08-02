#include "log.h"

#include <functional>
#include <map>
#include <time.h>
#include <stdio.h>
#include <config.h>


namespace rainbow {

LogLevel::Level LogLevel::FromString(const std::string& str) {
#define XX(name) \
    if (str == #name) { \
        return LogLevel::name; \
    }
    XX(UNKNOW);
    XX(DEBUG);
    XX(INFO);
    XX(WARN);
    XX(ERROR);
    XX(FATAL);
    return LogLevel::UNKNOW;
#undef XX

}

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
    NameFormatItem(const std::string& str = "") {}
    void format(std::ostream& os, Logger::ptr logger,
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

/**
 * 获取省略号指定的参数
 */
void LogEvent::format(const char* fmt, ...) {
    va_list al;
    va_start(al, fmt);
    format(fmt, al);
    va_end(al);
}

/**
 * 将参数输出到m_ss中（格式化写入）
 */
void LogEvent::format(const char* fmt, va_list al) {
    char* buf = nullptr;
    int len = vasprintf(&buf, fmt, al);
    
    /*
     * (gdb) p fmt
     * $3 = 0x414228 "test macro fmt error %s"
     * 从这个结果中可以看出 fmt 在原有字符串的基础上加入了
     * 对变长参数的格式化输出，从而能够像使用 printf 函数那样
     * 对参数进行输出
     */
    if (len != -1) {
        m_ss << std::string(buf, len);
        free(buf);
    }
}


LogEventWrap::LogEventWrap(LogEvent::ptr e) : m_event(e) {

}

/**
 * 析构函数触发 LogEvent 将日志信息写入到 LogAppender中
 */
LogEventWrap::~LogEventWrap() {
    m_event->getLogger()->log(m_event->getLevel(), m_event);
}

/*
 * 获取日志信息
 */
std::stringstream& LogEventWrap::getSS() {
    return m_event->getSS();
}

/*
 * 设置日志名称，日志级别以及日志格式
 */
Logger::Logger(const std::string& name)
    : m_name(name), m_level(LogLevel::DEBUG) {
    m_formatter.reset(new LogFormatter("%d%T%t%T%F%T[%p]%T%c%T%f:%l%T%m%n"));
}

void Logger::setFormatter(LogFormatter::ptr val) {
    m_formatter = val;
}
void Logger::setFormatter(const std::string& val) {
    rainbow::LogFormatter::ptr new_val(new rainbow::LogFormatter(val));
    if (new_val->isError()) {
        std::cout << "Logger setFormatter name = " << m_name
                  << " value = " << val << " invalid formatter"
                  << std::endl;
        return ;
    }
    m_formatter = new_val;
}

LogFormatter::ptr Logger::getFormatter() const {
    return m_formatter;
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


void Logger::clearAppenders() {
    m_appenders.clear();
}

void Logger::log(LogLevel::Level level, LogEvent::ptr event) {
    if (level >= m_level) {
        auto self = shared_from_this();
        if (!m_appenders.empty()) {
            for (auto& it : m_appenders) {
                it->log(self, level, event);
            }
        } else if (m_root) {
            m_root->log(level, event); 
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

std::string FileLogAppender::toYamlString() {
    YAML::Node node;
    node["type"] = "FileLogAppender";
    node["file"] = m_filename;
    std::stringstream ss;
    ss << node;
    return  ss.str();
}

void StdoutLogAppender::log(std::shared_ptr<Logger> logger,
                            LogLevel::Level level, LogEvent::ptr event) {
    if (level >= m_level) {
        std::cout << m_formatter->format(logger, level, event);
    }
}


std::string StdoutLogAppender::toYamlString() {
    YAML::Node node;
    node["type"] = "StdoutLogAppender";
    std::stringstream ss;
    ss << node;
    return  ss.str();
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
                m_error = true;
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
    m_loggers[m_root->m_name] = m_root;
    init();
}

std::string FileLogAppender::toYamlString() override {
    YAML::Node node;
    node["name"] = m_name;
    node["level"] = LogLevel::ToString(m_level);
    if (!m_formatter.empty()) {
        node["formatter"] = m_formatter;
    }
    std::stringstream ss;
    ss << node;
    return  ss.str();
}

Logger::ptr LoggerManager::getLogger(const std::string& name) {
    auto it = m_loggers.find(name);
    if (it != m_loggers.end()) {
        return it->second;
    }

    Logger::ptr logger(new Logger(name));
    logger->m_root = m_root;
    m_loggers[name] = logger;
    return logger;
}

struct LogAppenderDefine {
    int type = 0; // 1 File, 2 Stdout
    LogLevel::Level level = LogLevel::UNKNOW;
    std::string formatter;
    std::string file;

    bool operator==(const LogAppenderDefine& oth) const {
        return type == oth.type
            && level == oth.level
            && formatter == oth.formatter
            && file == oth.file;
    }
};

struct LogDefine {
    std::string name;
    LogLevel::Level level = LogLevel::UNKNOW;
    std::string formatter;

    std::vector<LogAppenderDefine> appenders;

    bool operator==(const LogDefine& oth) const {
        return name == oth.name
            && level == oth.level
            && formatter == oth.formatter
            && appenders == appenders;
    }

    bool operator<(const LogDefine& oth) const {
        return name < oth.name;
    }

};

//偏特化
template<>
class LexicalCast<std::string, std::set<LogDefine> > {
public:
    std::set<LogDefine> operator()(const std::string& v) {
        YAML::Node node = YAML::Load(v);
        std::set<LogDefine> s_set;
        for (size_t i = 0; i < node.size(); ++i) {
            auto n = node[i];
            if (!n["name"].IsDefined()) {
                std::cout << "log config error: name is null, " << n
                          << std::endl;
                continue;
            }

            LogDefine ld;
            ld.name = n["name"].as<std::string>();
            ld.level = LogLevel::FromString(n["level"].IsDefined() ? n["level"].as<std::string>() : "");
            if (n["formatter"].IsDefined()) {
                ld.formatter = n["formatter"].as<std::string>(); 
            }

            if (n["appenders"].IsDefined()) {
                for (size_t x = 0; x < n["appenders"].size(); ++x) {
                    auto a = n["appenders"][x];
                    if (!a["type"].IsDefined()) {
                         std::cout << "log config error: appender type is null, " << a 
                                   << std::endl;
                         continue;
                    }
                    std::string type = a["type"].as<std::string>();
                    LogAppenderDefine lad;
                    if (type == "FileLogAppender") {
                        lad.type = 1;
                        if (!a["file"].IsDefined()) {
                             std::cout << "log config error: fileappender file is null, " << a 
                                       << std::endl;
                             continue;
                        }
                        lad.file = a["file"].as<std::string>();
                        if (a["formatter"].IsDefined()) {
                            lad.formatter = a["formatter"].as<std::string>();
                        }
                    } else if (type == "StdoutLogAppender") {
                        lad.type = 2;
                        if (a["formatter"].IsDefined()) {
                            lad.formatter = a["formatter"].as<std::string>();
                        }
                    } else {
                         std::cout << "log config error: appender type is invalid, " << a 
                                   << std::endl;
                         continue;
                    }
                    ld.appenders.push_back(lad);
                }
            }
            s_set.insert(ld);
        }
        return s_set;
    }

};

template<>
class LexicalCast<std::set<LogDefine>, std::string> {
public:
    std::string operator()(const std::set<LogDefine>& v) {
        YAML::Node node(YAML::NodeType::Sequence);
        for (auto& i : v) {
            YAML::Node n;
            n["name"] = i.name;
            n["level"] = LogLevel::ToString(i.level);
            if (i.formatter.empty()) {
                n["level"] = i.formatter;
            }

            for (auto& a : i.appenders) {
                YAML::Node na;
                if (a.type == 1) {
                    na["type"] = "FileLogAppender";
                    na["file"] = a.file;
                } else if (a.type == 2) {
                    na["type"] = "StdoutLogAppender";
                }
                na["level"] = LogLevel::ToString(a.level);

                if (!a.formatter.empty()) {
                    na["formatter"] = a.formatter; 
                }

                n["appenders"].push_back(na);
            }
            node.push_back(n);
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};

rainbow::ConfigVar<std::set<LogDefine>>::ptr g_log_define = 
    rainbow::Config::Lookup("logs", std::set<LogDefine>(), "logs config");

struct LogIniter {
    LogIniter() {
        g_log_define->addListener(0xF1E231, [](const std::set<LogDefine>& old_value,
                    const std::set<LogDefine>& new_value) {
            RAINBOW_LOG_INFO(RAINBOW_LOG_ROOT()) << "on_logger_conf_changed";
            // 新增
            for (auto& i : new_value) {
                auto it = old_value.find(i);
                rainbow::Logger::ptr logger;
                if (it == old_value.end()) {
                    // 新增logger
                    logger.reset(new rainbow::Logger(i.name));
                } else {
                    if (!(i == *it)) {
                        // 修改的 logger
                        logger = RAINBOW_LOG_NAME(i.name);
                    }
                }
                logger->setLevel(i.level);
                if (!i.formatter.empty()) {
                    logger->setFormatter(i.formatter);
                }

                logger->clearAppenders();
                for (auto& a : i.appenders) {
                    rainbow::LogAppender::ptr ap;
                    if (a.type == 1) {
                        ap.reset(new FileLogAppender(a.file));
                    } else if (a.type == 2) {
                        ap.reset(new StdoutLogAppender);
                    }
                    ap->setLevel(a.level);
                    logger->addAppender(ap);
                }

            }

            for (auto& i : old_value) {
                auto it = new_value.find(i);
                if (it == new_value.end()) {
                    // 删除 logger
                    auto logger = RAINBOW_LOG_NAME(i.name);
                    logger->setLevel((LogLevel::Level)0);
                    logger->clearAppenders();
                }
            }
        });
    }
};

static LogIniter __log_init;

void LoggerManager::init() {

}
}  // namespace rainbow
