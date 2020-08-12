#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <iostream>
#include <string>
#include <mutex>
#include <fstream>

enum class LoggerLevel{
    DISABLE_ALL = 0,
    ERROR = 1,
    WARN = 2,
    INFO = 3,
    TRACE = 4,
    DEBUG = 5,
    ENABLE_ALL = 6,
};

enum class LoggerType{
    CONSOLE_LOG = 1,
    FILE_LOG = 2,
    CONSOLE_FILE_LOG =3,
};

class Logger{
private:

    LoggerType loggerType;
    LoggerLevel loggerLevel;
    std::mutex fileMutex;
    std::ofstream logFile;
    Logger();
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;
    ~Logger();
    std::string getCurrentTime();
    void logToFile(std::string &text);
    void logToConsole(std:: string &text);

public:

    static Logger& getInstance();
    void error(std::string &text);
    void error(const char *text);
    void warn(std::string &text);
    void warn(const char *text);
    void info(std::string &text);
    void info(const char *text);
    void trace(std::string &text);
    void trace(const char *text);
    void debug(std::string &text);
    void debug(const char *text);
    void setLoggerLevel(LoggerLevel level);
    void setLoggerType(LoggerType type);
    void disableLogging();
    void enableLogging();
    bool isConsoleLoggingEnabled();
    bool isFileLoggingEnabled();
};
#endif
