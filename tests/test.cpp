#include <iostream>
#include "../rainbow/log.h"
#include "../rainbow/util.h"

int main(int argc, char** argv) {

    rainbow::Logger::ptr logger(new rainbow::Logger);
    logger->addAppender(rainbow::LogAppender::ptr(new rainbow::StdoutLogAppender));

    rainbow::LogFormatter::ptr fmt(new rainbow::LogFormatter("%d%T%p%T%m%n"));
    rainbow::FileLogAppender::ptr file_appender(new rainbow::FileLogAppender("bin/log.txt"));
    file_appender->setFormatter(fmt);
    file_appender->setLevel(rainbow::LogLevel::ERROR);

    logger->addAppender(file_appender);

    //rainbow::LogEvent::ptr event(new rainbow::LogEvent(logger, rainbow::LogLevel::DEBUG, __FILE__, __LINE__, 0, rainbow::GetThreadId(), rainbow::GetFiberId(), time(0)));

    //event->getSS() << "hello rainbow!" << std::endl;

    //logger->log(rainbow::LogLevel::DEBUG, event);
    //std::cout << "hello rainbow log" << std::endl;
    
    RAINBOW_LOG_INFO(logger) << "test macro";
    RAINBOW_LOG_ERROR(logger) << "test ERROR";
   
    RAINBOW_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");
    RAINBOW_LOG_FMT_DEBUG(logger, "test macro fmt debug %s", "bb");

    auto l = rainbow::LoggerMgr::GetInstance()->getLogger("xx");
    RAINBOW_LOG_INFO(l) << "test LoggerMgr";

    return 0;
}

