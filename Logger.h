#pragma once
#include"noncopyable.h"
#include<string>
#define LOG_INFO(logmsgFormat,...)\
do\
{\
    Logger &logger=Logger::instance();\
    logger.setLogLevel(INFO);\
    char buf[1024]={0};\
    sprintf(buf,1024,logmsgFormat,##__VA_ARGS__);\
    logger.log(buf);\
}while(0)

#define LOG_ERROR(logmsgFormat,...)\
do\
{\
    Logger &logger=Logger::instance();\
    logger.setLogLevel(ERROR);\
    char buf[1024]={0};\
    sprintf(buf,1024,logmsgFormat,##__VA_ARGS__);\
    logger.log(buf);\
}while(0)

#define LOG_FATAL(logmsgFormat,...)\
do\
{\
    Logger &logger=Logger::instance();\
    logger.setLogLevel(FATAL);\
    char buf[1024]={0};\
    sprintf(buf,1024,logmsgFormat,##__VA_ARGS__);\
    logger.log(buf);\
}while(0)

#ifdef MUDEBUG
#define LOG_DEBUG(logmsgFormat,...)\
do\
{\
    Logger &logger=Logger::instance();\
    logger.setLogLevel(DEBUG);\
    char buf[1024]={0};\
    sprintf(buf,1024,logmsgFormat,##__VA_ARGS__);\
    logger.log(buf);\
}while(0)
#else
    #define LOG_DEBUG(logmsgFormat,...)
#endif
//定义日志的级别 INFO ERROR FATAL DEBUG
enum LogLevel
{
    INFO,
    ERROR,
    FATAL,
    DEBUG,
};
//日志类
class Logger:public noncopyable
{
    public:
    static Logger& instance();//用指针或引用都可，引用用.方便一丢丢
    void setLogLevel(int Level);
    void log(std::string msg);
    private:
    int logLevel_;
    Logger();
};