#include <iostream>
#include "Logger.hpp"

#define DEFAULT_LOG_FILENAME "log_messages"
#define FILE_EXTENSION ".log"
#define MAX_DATE 20

using namespace std;

Logger::Logger(){
    initLoggingType();
    initLoggingLevel();
}

void Logger::initLoggingType(){
    loggerType = LoggerType::CONSOLE_FILE_LOG;
    if(isFileLoggingEnabled()){
        time_t now = time(0);
        char the_date[MAX_DATE];
        strftime(the_date, MAX_DATE, "%Y%m%d%H%M%S", localtime(&now));
        string filename = DEFAULT_LOG_FILENAME + string(the_date)+ FILE_EXTENSION;
        logFile.open(filename, ios::out|ios::app);
    }
}

void Logger::initLoggingLevel(){
    loggerLevel = LoggerLevel::INFO;
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

void Logger::disableLogging(){
    setLoggerLevel(LoggerLevel::DISABLE_ALL);
}

void Logger::enableLogging(){
    setLoggerLevel(LoggerLevel::INFO);
}

bool Logger::isFileLoggingEnabled(){
    if(loggerType == LoggerType::FILE_LOG || loggerType == LoggerType::CONSOLE_FILE_LOG)
        return true;
    return false;
}

bool Logger::isConsoleLoggingEnabled(){
    if(loggerType == LoggerType::CONSOLE_LOG || loggerType == LoggerType::CONSOLE_FILE_LOG)
        return true;
    return false;
}

void Logger::logError(string &text){
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

void Logger::logWarn(string &text){
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

void Logger::logInfo(string &text){
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

void Logger::logTrace(string &text){
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

void Logger::logDebug(string &text){
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
