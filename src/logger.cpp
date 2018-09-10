#include "logger.h"

#include <typeinfo>

using namespace utils;

Logger *Logger::_ptr {nullptr};


void Logger::initialize(const std::string &log_file_path) {
  initialize(LogLevel::DEBUG, log_file_path);
  initialize(LogLevel::INFO, log_file_path);
  initialize(LogLevel::ERROR, log_file_path);
}


void Logger::initialize(std::ostream &out) {
  initialize(LogLevel::DEBUG, out);
  initialize(LogLevel::INFO, out);
  initialize(LogLevel::ERROR, out);
}


void Logger::initialize(LogLevel level, const std::string &log_file_path) {
  try {
    if ( _ptr && _ptr->_level_map.at(int(level)) )
      return;
  }
  catch(...){
  }

  std::ofstream *log_file = new std::ofstream(log_file_path, std::ios::ate | std::ios::app);

  if ( !log_file->is_open() )
    throw std::string("Log File cannot be opened: " + log_file_path);

  initialize(level, *log_file);
}


void Logger::initialize(LogLevel level, std::ostream &out) {
  if ( !_ptr )
    _ptr = new Logger();

  _ptr->_level_map.insert(std::pair<int, std::ostream&>(int(level), out));
}


void Logger::log(LogLevel level, std::string trace) {
  static const std::string HEADERS[] { "DEBUG: ", "INFO: ", "***********************************************************************\nERROR: "};
  static const std::string TAILS[]   { "\n\n", "\n\n", "\n***********************************************************************\n\n"};
  try {
      _ptr->_level_map.at(int(level)) << HEADERS[int(level)] << trace << TAILS[int(level)];
      _ptr->_level_map.at(int(level)).flush();
  }
  catch(...) {
    std::cout << "Debug Level not initialized.";
  }
}


void Logger::destroy() {
  auto map_iter = _ptr->_level_map.begin();
  while ( map_iter != _ptr->_level_map.end() ) {
    if ( typeid((map_iter)->second) == typeid(std::ofstream) ) {
      dynamic_cast<std::ofstream&>(map_iter->second).close();
      delete &(map_iter++)->second;
    }
    else
      map_iter++;
  }

  delete _ptr;
}


