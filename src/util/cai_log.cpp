#include "termcolor/termcolor.hpp"
#include "util/cai_log.h"

namespace cai::cailog {

auto Logger::get() -> Logger& {
  static Logger instance;
  return instance;
}

void Logger::set_log_level(LogLevel log_level) {
  log_level_ = log_level;
}

template <typename... Args>
void Logger::trace(const std::string& msg, Args &&... args) {
  if (log_level_ > LogLevel::TRACE) {
    return;
  }

  std::cout << termcolor::cyan << "[TRACE]: " << termcolor::reset;
  printf(msg.c_str(), args...);
}

template <typename... Args>
void Logger::info(const std::string& msg, Args &&... args) {
  if (log_level_ > LogLevel::INFO) {
    return;
  }

  std::cout << termcolor::green << "[INFO]: " << termcolor::reset;
  printf(msg.c_str(), args...);
}

template <typename... Args>
void Logger::warn(const std::string& msg, Args &&... args) {
  if (log_level_ > LogLevel::WARN) {
    return;
  }

  std::cout << termcolor::yellow << "[WARN]: " << termcolor::reset;
  printf(msg.c_str(), args...);
}

template <typename... Args>
void Logger::error(const std::string& msg, Args &&... args) {
  if (log_level_ > LogLevel::ERROR) {
    return;
  }

  std::cout << termcolor::red << "[ERROR]: " << termcolor::reset;
  printf(msg.c_str(), args...);
}

template <typename... Args>
void Logger::fatal(const std::string& msg, Args &&... args) {
  if (log_level_ > LogLevel::FATAL) {
    return;
  }

  std::cout << termcolor::red << "[FATAL]: " << termcolor::reset;
  printf(msg.c_str(), args...);
  throw std::runtime_error("Fatal error");
}

}  // namespace cai::cailog