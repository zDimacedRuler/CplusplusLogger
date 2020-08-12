#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <iostream>
#include <string>
#include <sstream>
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
    
    template<typename T>
    void constructMessage(std::ostringstream &os, T arg1){
        os<<arg1;
    }

    template<typename T, typename... Args>
    void constructMessage(std::ostringstream &os, T arg1, Args... args){
        os<<arg1<<" : ";
        constructMessage(os,args...);
    }

    void Error(std::string &text);
    void Warn(std::string &text);
    void Info(std::string &text);
    void Trace(std::string &text);
    void Debug(std::string &text);

public:

    static Logger& getInstance();

    template<typename... Args>
    void error(Args... args){
        std::ostringstream os;
        constructMessage(os, args...);
        std::string text = os.str();
        Error(text);
    }

    template<typename... Args>
    void warn(Args... args){
        std::ostringstream os;
        constructMessage(os, args...);
        std::string text = os.str();
        Warn(text);
    }

    template<typename... Args>
    void info(Args... args){
        std::ostringstream os;
        constructMessage(os, args...);
        std::string text = os.str();
        Info(text);
    }

    template<typename... Args>
    void trace(Args... args){
        std::ostringstream os;
        constructMessage(os, args...);
        std::string text = os.str();
        Trace(text);
    }

    template<typename... Args>
    void debug(Args... args){
        std::ostringstream os;
        constructMessage(os, args...);
        std::string text = os.str();
        Debug(text);
    }

    void setLoggerLevel(LoggerLevel level);
    void setLoggerType(LoggerType type);
    void disableLogging();
    void enableLogging();
    bool isConsoleLoggingEnabled();
    bool isFileLoggingEnabled();
};
#endif
