#include "Logger.h"
#include"Timestamp.h"
#include <iostream>


Logger &Logger::instance()
{
    static Logger logger;
    return logger;
}
void Logger::setLogLevel(int level)
{
    logLevel_ = level;
}
//[级别信息] time ：msg
void Logger::log(std::string msg)
{
    switch (logLevel_)
    {
    case INFO:
        /* code */
        std::cout << "[INFO]";
        break;
    case ERROR:
        /* code */
        std::cout << "[ERROR]";
        break;
    case FATAL:
        /* code */
        std::cout << "[FATAL]";
        break;
    case DEBUG:
        /* code */
        std::cout << "[DEBUG]";
        break;

    default:
        break;
    }
    //打印时间msg
    std::cout<<Timestamp::now().toSTring()<<":"<<msg<<std::endl;
}