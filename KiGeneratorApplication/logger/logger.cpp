#include "logger.h"

Logger Logger::self;
Logger::Logger()
{
#ifdef LOGGER_SPD
    time_t rawtime;
    struct tm* timeinfo;
    char buffer[80];
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", timeinfo);
    std::string str(buffer);
    mLogDir = "../log/applog_" + str;
    struct stat st;
    //    S_ISDIR — directory
    //    S_ISREG — regular file
    //    S_ISCHR — character device
    //    S_ISBLK — block device
    //    S_ISFIFO — FIFO
    //    S_ISLNK — symbolic link
    //    S_ISSOCK — socket

    if ((stat("../log", &st) == 0) && S_ISDIR(st.st_mode))
    {
        printf(" /log folder is present\n");
    }
    else
    {
        printf(" /log folder is not present\n");
#ifdef __linux__
        int result = mkdir("../log", 0777);
#elif _WIN32
        int result = mkdir("../log");
#endif
        printf("mkdir = %d\n", result);
    }

    if ((stat(mLogDir.c_str(), &st) == 0) && S_ISDIR(st.st_mode))
    {
        printf(" /log_dir is present\n");
    }
    else
    {
        printf(" /log_dir is not present\n");
#ifdef __linux__
        int result = mkdir(mLogDir.c_str(), 0777);
#elif _WIN32
        int result = mkdir(mLogDir.c_str());
#endif
        printf("mkdir = %d\n", result);
    }

    std::string logApplicationFileName = "/application.log";
    logApplicationFileName = mLogDir + logApplicationFileName;
    //initiate log
    stdoutSink = std::make_shared<spdlog::sinks::stdout_sink_mt>();
    fileSink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(logApplicationFileName,
                                                                      MAX_ROTATE_FILE_SIZE,
                                                                      MAX_ROTATE_FILES);
    sinks.push_back(stdoutSink);
    sinks.push_back(fileSink);
    applogger = std::make_shared<spdlog::logger>(APP_LOGGER_NAME,
                                                 begin(sinks),
                                                 end(sinks));
    applogger->set_level(spdlog::level::trace);
    applogger->flush_on(spdlog::level::debug);
    //        applogger->set_formatter()
    spdlog::register_logger(applogger);
    std::string t = "ducls";
    applogger->trace("Init logger successful %s", t.c_str());
    applogger->debug("Init logger successful %s", t.c_str());
    applogger->info("Init logger successful %s", t.c_str());
    applogger->warn("Init logger successful %s", t.c_str());
    applogger->error("Init logger successful {}", t.c_str());
#endif
}

Logger* Logger::getInstance()
{
    return &Logger::self;
}

void Logger::init()
{
#ifdef LOGGER_STDOUT
#endif
#ifdef LOGGER_SPD
#endif
}

#ifdef LOGGER_SPD
std::string Logger::getLogDir() const
{
    return mLogDir;
}
#endif

