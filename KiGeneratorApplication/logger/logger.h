/*
 * Logger.h
 *
 *  Created on: Aug 27, 2015
 *      Author: ttdk
 */

#ifndef LOGGER_H_
#define LOGGER_H_


#include <string>
#include <string.h>
#include <stdio.h>
//#define LOGGER_STDOUT
#define LOGGER_SPD


#ifdef LOGGER_SPD

#include "spdlog/spdlog.h"

#define _SPDLOG_STR_H(x) #x
#define _SPDLOG_STR_HELPER(x) _SPDLOG_STR_H(x)
//#  define SPDLOG_TRACE(logger, ...) logger->trace("[ " __FILE__ ":" SPDLOG_STR_HELPER(__LINE__) " ] " __VA_ARGS__)
#define LOG_DEBUG(...) {\
    Logger::getInstance()->applogger->debug("[ " __FILE__ ":" _SPDLOG_STR_HELPER(__LINE__) " ] " __VA_ARGS__);\
}
#define LOG_INFO(...) {\
    Logger::getInstance()->applogger->info("[ " __FILE__ ":" _SPDLOG_STR_HELPER(__LINE__) " ] " __VA_ARGS__);\
}
#define LOG_ERROR(...) {\
    Logger::getInstance()->applogger->error("[ " __FILE__ ":" _SPDLOG_STR_HELPER(__LINE__) " ] " __VA_ARGS__);\
}
// define parameters for log file
//using namespace spdlog;
#define APP_LOGGER_NAME "vtx_logger"
#define MAX_ROTATE_FILE_SIZE 1024*10000         //10 MB
#define MAX_ROTATE_FILES 5
#endif
#ifdef LOGGER_STDOUT
#include <stdio.h>
#define LOG_DEBUG(...) {\
    char prefixStr[100] = {0};\
    char str[1000] = {0}; \
        sprintf(prefixStr,"%60s:%-4d ",__FILE__, __LINE__);\
    sprintf(str, __VA_ARGS__); \
        std::string msg;\
    msg.append(prefixStr);\
    msg.append(str);\
    printf("[DEBUG] %s\n", msg.c_str()); \
}

#define LOG_INFO(...) {\
    char prefixStr[100] = {0};\
    char str[1000] = {0}; \
        sprintf(prefixStr,"%60s:%-4d ",__FILE__, __LINE__);\
    sprintf(str, __VA_ARGS__); \
        std::string msg;\
    msg.append(prefixStr);\
    msg.append(str);\
    printf("[INFO] %s\n", msg.c_str()); \
}

#define LOG_WARN(...) {\
    char prefixStr[100] = {0};\
    char str[1000] = {0}; \
        sprintf(prefixStr,"%60s:%-4d ",__FILE__, __LINE__);\
    sprintf(str, __VA_ARGS__); \
        std::string msg;\
    msg.append(prefixStr);\
    msg.append(str);\
    printf("[WARN] %s\n", msg.c_str()); \
}

#define LOG_ERROR(...) {\
    char prefixStr[100] = {0};\
    char str[1000] = {0}; \
        sprintf(prefixStr,"%60s:%-4d ",__FILE__, __LINE__);\
    sprintf(str, __VA_ARGS__); \
        std::string msg;\
    msg.append(prefixStr);\
    msg.append(str);\
    printf("[ERROR] %s\n", msg.c_str()); \
}
#endif

class Logger
{
    public:
        Logger();

        static Logger* getInstance() ;

        static void init() ;

#ifdef LOGGER_SPD
        //puclic applogger for easy to access
        std::shared_ptr<spdlog::logger> applogger;
        std::string getLogDir() const;
#endif


    private:
        static Logger self;
#ifdef LOGGER_SPD
        std::string mLogDir;
        //spd log declare:
        std::vector<spdlog::sink_ptr> sinks;
        spdlog::sink_ptr fileSink;
        spdlog::sink_ptr stdoutSink;
#endif
};
#endif /* LOGGER_H_ */
