#ifndef _LOGGER_HPP_
#define _LOGGER_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <mutex>
#include <fstream>

#define Error(args...) Logger::getInstance().error(args)
#define Warn(args...) Logger::getInstance().warn(args)
#define Info(args...) Logger::getInstance().info(args)
#define Trace(args...) Logger::getInstance().trace(args)
#define Debug(args...) Logger::getInstance().debug(args)

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

    //Logging Type Can only be changed from confg file
    void initLoggingType();
    void initLoggingLevel();

    void logError(std::string &text);
    void logWarn(std::string &text);
    void logInfo(std::string &text);
    void logTrace(std::string &text);
    void logDebug(std::string &text);

public:

    static Logger& getInstance();

    template<typename... Args>
    void error(Args... args){
        std::ostringstream os;
        constructMessage(os, args...);
        std::string text = os.str();
        logError(text);
    }

    template<typename... Args>
    void warn(Args... args){
        std::ostringstream os;
        constructMessage(os, args...);
        std::string text = os.str();
        logWarn(text);
    }

    template<typename... Args>
    void info(Args... args){
        std::ostringstream os;
        constructMessage(os, args...);
        std::string text = os.str();
        logInfo(text);
    }

    template<typename... Args>
    void trace(Args... args){
        std::ostringstream os;
        constructMessage(os, args...);
        std::string text = os.str();
        logTrace(text);
    }

    template<typename... Args>
    void debug(Args... args){
        std::ostringstream os;
        constructMessage(os, args...);
        std::string text = os.str();
        logDebug(text);
    }
    int getLoggerLevel(){
        return (static_cast<int>(loggerLevel));
    };
    void setLoggerLevel(LoggerLevel level);
    void disableLogging();
    void enableLogging();
    bool isConsoleLoggingEnabled();
    bool isFileLoggingEnabled();
};
#endif
