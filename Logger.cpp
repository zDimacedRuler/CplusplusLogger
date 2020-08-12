#include <iostream>
#include "Logger.hpp"

#define DEFAULT_LOG_FILENAME "log_messages.log"

using namespace std;

Logger::Logger(){
    loggerType = LoggerType::CONSOLE_LOG;
    loggerLevel = LoggerLevel::INFO;
    logFile.open(DEFAULT_LOG_FILENAME, ios::out|ios::app);
}

Logger::~Logger(){
    if(logFile.is_open())
        logFile.close();
}

Logger& Logger::getInstance(){
    static Logger logger;
    return logger;
}

string Logger::getCurrentTime(){
    string currTime;
    time_t now = time(0); 
    currTime.assign(ctime(&now));

    // removing Last charactor of currentTime which is "\n"
    currTime = currTime.substr(0, currTime.size()-1);
    return currTime;    
}

void Logger::logToFile(string &text){
    lock_guard<mutex> guard(fileMutex);
    logFile<< getCurrentTime() << " " << text << endl;
}

void Logger::logToConsole(string &text){
    cout<< getCurrentTime() << " " << text << endl;
}

void Logger::setLoggerLevel(LoggerLevel level){
    loggerLevel = level;
}

void Logger::setLoggerType(LoggerType type){
    loggerType = type;
}

void Logger::disableLogging(){
    setLoggerLevel(LoggerLevel::DISABLE_ALL);
}

void Logger::enableLogging(){
    setLoggerLevel(LoggerLevel::INFO);
}

bool Logger::isFileLoggingEnabled(){
    if(loggerType == LoggerType::CONSOLE_LOG || loggerType == LoggerType::CONSOLE_FILE_LOG)
        return true;
    return false;
}

bool Logger::isConsoleLoggingEnabled(){
    if(loggerType == LoggerType::FILE_LOG || loggerType == LoggerType::CONSOLE_FILE_LOG)
        return true;
    return false;
}

void Logger::Error(string &text){
    string message;
    message.append(" [E] ");
    message.append(text);
    
    //logging to file
    if(isFileLoggingEnabled() && loggerLevel >= LoggerLevel::ERROR)
        logToFile(message);

    //logging to console
    if(isConsoleLoggingEnabled() && loggerLevel >= LoggerLevel::ERROR)
        logToConsole(message);
}

void Logger::Warn(string &text){
    string message;
    message.append(" [W] ");
    message.append(text);

    //logging to file
    if(isFileLoggingEnabled() && loggerLevel >= LoggerLevel::WARN)
        logToFile(message);

    //logging to console
    if(isConsoleLoggingEnabled() && loggerLevel >= LoggerLevel::WARN)
        logToConsole(message);
}

void Logger::Info(string &text){
    string message;
    message.append(" [I] ");
    message.append(text);

    //logging to file
    if(isFileLoggingEnabled() && loggerLevel >= LoggerLevel::INFO)
        logToFile(message);

    //logging to console
    if(isConsoleLoggingEnabled() && loggerLevel >= LoggerLevel::INFO)
    logToConsole(message);
}

void Logger::Trace(string &text){
    string message;
    message.append(" [T] ");
    message.append(text);

    //logging to file
    if(isFileLoggingEnabled() && loggerLevel >= LoggerLevel::TRACE)
        logToFile(message);

    //logging to console
    if(isConsoleLoggingEnabled() && loggerLevel >= LoggerLevel::TRACE)
        logToConsole(message);
}

void Logger::Debug(string &text){
    string message;
    message.append(" [D] ");
    message.append(text);

    //logging to file
    if(isFileLoggingEnabled() && loggerLevel >= LoggerLevel::DEBUG)
        logToFile(message);

    //logging to console
    if(isConsoleLoggingEnabled() && loggerLevel >= LoggerLevel::DEBUG)
        logToConsole(message);
}
