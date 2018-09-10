#ifndef LOGGER_H
#define LOGGER_H


// For non RELESAE or Library BUILD targets the logging is performed using "cout"
#if !defined RELEASE_BUILD & !defined LIB_BUILD
  #include <iostream>

  #define INIT_LOG(x)
  #define INIT_LOG_LEVEL(level, out)
  #define DESTROY_LOG

  #define DEBUG_LOG(trace)  std::cout << "DEBUG: " << trace << std::endl << std::endl
  #define INFO_LOG(trace)   std::cout << "INFO: " << trace << std::endl << std::endl
  #define ERROR_LOG(trace)  std::cout << "***********************************************************************" << std::endl \
                                      << "ERROR: " << trace << std::endl \
                                      << "***********************************************************************" << std::endl << std::endl
#else
  #define LEV_ERROR  utils::LogLevel::ERROR
  #define LEV_INFO   utils::LogLevel::INFO
  #define LEV_DEBUG  utils::LogLevel::DEBUG

  #define INIT_LOG(out)               utils::Logger::initialize(out)
  #define INIT_LOG_LEVEL(level, out)  utils::Logger::initialize(level, out)
  #define DESTROY_LOG                 utils::Logger::destroy()

  #define ERROR_LOG(trace) utils::Logger::log(utils::LogLevel::ERROR, trace)

  #ifdef DEBUG_LOG_LEVEL
    #define DEBUG_LOG(trace)  utils::Logger::log(utils::LogLevel::DEBUG, trace)
    #define INFO_LOG(trace)   utils::Logger::log(utils::LogLevel::INFO, trace)
  #elif defined INFO_LOG_LEVEL
    #define DEBUG_LOG(trace)
    #define INFO_LOG(trace)   utils::Logger::log(utils::LogLevel::INFO, trace)
  #else
    #define DEBUG_LOG(trace)
    #define INFO_LOG(trace)
  #endif // LOG_LEVEL

  #include <iostream>
  #include <fstream>
  #include <string>
  #include <map>

  namespace utils
  {
    enum class LogLevel {DEBUG, INFO, ERROR};

    class Logger
    {
    public:
      static void initialize(const std::string &log_file_path);
      static void initialize(std::ostream &out);
      static void initialize(LogLevel level, const std::string &log_file_path);
      static void initialize(LogLevel level, std::ostream &out);

      static void log(LogLevel level, std::string trace);

      static void destroy();

    private:
      static Logger *_ptr;

      std::map<int, std::ostream&> _level_map;

      Logger(){}
      ~Logger(){}
    };

  }

#endif // RELEASE_TARGET


#endif // LOGGER_H
