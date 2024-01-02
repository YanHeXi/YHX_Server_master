#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <list>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <functional>

namespace yhx
{
    class Logger;

    class LogLevel
    {
    public:
        enum Level
        {
            UNKNOW = 0,
            DEBUG = 1,
            INFO = 2,
            WARN = 3,
            ERROR = 4,
            FATAL = 5
        };
        static const char *ToString(LogLevel::Level level);
        static LogLevel::Level FromString(const std::string &str);
    };

    class LogEvent
    {
    public:
        using ptr = std::shared_ptr<LogEvent>;
        LogEvent();

        const char *getFile() const { return m_file; }

        int32_t getLine() const { return m_line; }

        uint32_t getElapse() const { return m_elapse; }

        uint32_t getThreadId() const { return m_threadId; }

        uint32_t getFiberId() const { return m_fiberId; }

        uint64_t getTime() const { return m_time; }

        const std::string &getThreadName() const { return m_threadName; }

        std::string getContent() const { return m_ss.str(); }

        std::shared_ptr<Logger> getLogger() const { return m_logger; }

        LogLevel::Level getLevel() const { return m_level; }

        std::stringstream &getSS() { return m_ss; }

        void format(const char *fmt, ...);

        void format(const char *fmt, va_list al);

    private:
        const char *m_file = nullptr;
        int32_t m_line = 0;
        uint32_t m_elapse = 0;
        uint32_t m_threadId = 0;
        uint32_t m_fiberId = 0;
        uint64_t m_time = 0;
        std::string m_threadName;
        std::stringstream m_ss;
        std::shared_ptr<Logger> m_logger;
        LogLevel::Level m_level;
    };
    class LogFormatter
    {
    public:
        using ptr = std::shared_ptr<LogFormatter>;
        LogFormatter(const std::string &pattern);
        std::string format(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event);

    public:
        class FormatItem
        {
        public:
            using ptr = std::shared_ptr<FormatItem>;
            FormatItem(const std::string &fmt = "root");
            virtual ~FormatItem();
            virtual void format(std::ostream &os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) = 0;
        };
        void init();

    private:
        std::string m_pattern;
        std::vector<FormatItem::ptr> m_items;
        bool m_error = false;
    };
    class LogAppender
    {
        friend class Logger;

    public:
        using ptr = std::shared_ptr<LogAppender>;
        virtual ~LogAppender() {}
        virtual void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr) = 0;

        LogFormatter::ptr getFormatter() const { return m_formatter; }

    protected:
        LogLevel::Level m_level = LogLevel::DEBUG;
        bool m_hasFormatter = false;
        // MutexType m_mutex;
        LogFormatter::ptr m_formatter;
    };

    class Logger : public std::enable_shared_from_this<Logger>
    {
    public:
        using ptr = std::shared_ptr<Logger>;

        Logger(const std::string &name = "root");
        void log(LogLevel::Level level, LogEvent::ptr event);
        void debug(LogEvent::ptr event);
        void info(LogEvent::ptr event);
        void error(LogEvent::ptr event);
        void warn(LogEvent::ptr event);
        void fatal(LogEvent::ptr event);

        void addAppender(LogAppender::ptr event);
        void delAppender(LogAppender::ptr event);
        LogLevel::Level getLevel() const { return m_level; }
        void setLevel(LogLevel::Level val) { m_level = val; }
        const std::string &getName() const { return m_name; }

    private:
        std::string m_name;
        LogLevel::Level m_level;
        std::list<LogAppender::ptr> m_appenders;
    };
    class StdoutLogAppender : public LogAppender
    {
    public:
        using ptr = std::shared_ptr<StdoutLogAppender>;
        void log(Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override;
    };

    class FileLogAppender : public LogAppender
    {
    public:
        using ptr = std::shared_ptr<FileLogAppender>;
        FileLogAppender(const std::string &filename);
        void log(std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) override;
        bool reopen();

    private:
        std::string m_filename;
        std::ofstream m_filestream;
    };

    class MassageFormatter : public LogFormatter
    {
    public:
        void format(std::ostream &os, LogEvent::ptr event);
    };
} // namespace yhx
