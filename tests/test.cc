#include "../yhx/log.h"
#include "../yhx/util.h"
#include <iostream>

int main(int atgs, char **argv)
{

    yhx::Logger::ptr logger(new yhx::Logger);
    logger->addAppender(yhx::LogAppender::ptr(new yhx::StdoutLogAppender));

    yhx::FileLogAppender::ptr file_appender(new yhx::FileLogAppender("./log.txt"));
    yhx::LogFormatter::ptr fmt(new yhx::LogFormatter("%d%T%p%T%m%n"));

    logger->addAppender(file_appender);

    std::cout << "hello yhx log" << std::endl;

    YHX_LOG_INFO(logger) << "test macro";
    YHX_LOG_ERROR(logger) << "test macro error";

    YHX_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");

    auto l = yhx::LoggerMgr::GetInstance()->getLogger("xx");
    YHX_LOG_DEBUG(l) << "xxx";

    return 0;
}
