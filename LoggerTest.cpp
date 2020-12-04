#include <iostream>
#include "Logger.hpp"

using namespace std;

int main(){

    Logger &pLogger =  Logger::getInstance();
    cout<<"\n*****************************************************\n";
    cout<<"Default Log Level is INFO\n";
    cout<<"Logging Level:"<<pLogger.getLoggerLevel()<<endl;
    pLogger.error("Log level: LOG_ERROR","Heelo");
    pLogger.warn("Log level: LOG_WARN","This is a","test");
    pLogger.info("Log level: LOG_INFO");
    //from here it wont be logged
    pLogger.trace("Log level: LOG_TRACE");
    pLogger.debug("Log level: LOG_DEBUG");

    cout<<"\n*****************************************************\n";
    cout<<"Log Level is changed to DEBUG\n";
    pLogger.setLoggerLevel(LoggerLevel::DEBUG);
    //all statements will log
    cout<<"Logging Level:"<<pLogger.getLoggerLevel()<<endl;
    pLogger.error("Log level: LOG_ERROR");
    pLogger.warn("Log level: LOG_WARN");
    pLogger.info("Log level: LOG_INFO");
    pLogger.trace("Log level: LOG_TRACE");
    pLogger.debug("Log level: LOG_DEBUG");

    cout<<"\n*****************************************************\n";
    cout<<"Logging is  Disabled\n";
    pLogger.disableLogging();
    //no statement will log
    cout<<"Logging Level:"<<pLogger.getLoggerLevel()<<endl;
    pLogger.error("Log level: LOG_ERROR");
    pLogger.warn("Log level: LOG_WARN");
    pLogger.info("Log level: LOG_INFO");
    pLogger.trace("Log level: LOG_TRACE");
    pLogger.debug("Log level: LOG_DEBUG");

    cout<<"\n*****************************************************\n";
    cout<<"Logging is Enabled\n";
    pLogger.setLoggerLevel(LoggerLevel::TRACE);
    //logging is again enabled to level Info
    cout<<"Logging Level:"<<pLogger.getLoggerLevel()<<endl;
    cout<<pLogger.getLoggerLevel()<<endl;
    Error("Log level: LOG_ERROR","Testing");
    Warn("Log level: LOG_WARN","ha ha ");
    Info("Log level: LOG_INFO","id","aa","kk");
    Trace("Log level: LOG_TRACE");
    Debug("Log level: LOG_DEBUG");

    return 0;
}
