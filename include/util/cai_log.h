#pragma once

#include <string>
#include "termcolor/termcolor.hpp"

namespace cai::cailog {

enum class LogLevel {
  TRACE = 0,
  INFO,
  WARN,
  ERROR,
  FATAL
};

class Logger {
public:
  Logger() = default;
  Logger(const Logger &) = default;
  Logger(Logger &&) = delete;
  auto operator=(const Logger &) -> Logger & = default;
  auto operator=(Logger &&) -> Logger & = delete;
  ~Logger() = default;

  static auto get() -> Logger& {
    static Logger instance;
    return instance;
  }

  template <typename... Args>
  void trace(const std::string& msg, Args &&... args) {
    if (log_level_ > LogLevel::TRACE) {
      return;
    }

    std::cout << termcolor::cyan << "[TRACE]: " << termcolor::reset;
    // TODO(zhm): 如何处理 msg 为空的情况, 后面相同
    printf(msg.c_str(), args...);
  }

  template <typename... Args>
  void info(const std::string& msg, Args &&... args) {
    if (log_level_ > LogLevel::INFO) {
      return;
    }

    std::cout << termcolor::green << "[INFO]: " << termcolor::reset;
    printf(msg.c_str(), args...);
  }

  template <typename... Args>
  void warn(const std::string& msg, Args &&... args) {
    if (log_level_ > LogLevel::WARN) {
      return;
    }

    std::cout << termcolor::yellow << "[WARN]: " << termcolor::reset;
    printf(msg.c_str(), args...);
  }

  template <typename... Args>
  void error(const std::string& msg, Args &&... args) {
    if (log_level_ > LogLevel::ERROR) {
      return;
    }

    std::cout << termcolor::red << "[ERROR]: " << termcolor::reset;
    printf(msg.c_str(), args...);
  }

  template <typename... Args>
  void fatal(const std::string& msg, Args &&... args) {
    if (log_level_ > LogLevel::FATAL) {
      return;
    }

    std::cout << termcolor::red << "[FATAL]: " << termcolor::reset;
    printf(msg.c_str(), args...);
    throw std::runtime_error("Fatal error");
  }

  void set_log_level(LogLevel log_level) {
    log_level_ = log_level;
  }

private:
  LogLevel log_level_ = LogLevel::TRACE;
};

template <typename... Args>
void trace(const std::string& msg, Args &&... args) {
  Logger::get().trace(msg, std::forward<Args>(args)...);
}

template <typename... Args>
void info(const std::string& msg, Args &&... args) {
  Logger::get().info(msg, std::forward<Args>(args)...);
}

template <typename... Args>
void warn(const std::string& msg, Args &&... args) {
  Logger::get().warn(msg, std::forward<Args>(args)...);
}

template <typename... Args>
void error(const std::string& msg, Args &&... args) {
  Logger::get().error(msg, std::forward<Args>(args)...);
}

template <typename... Args>
void fatal(const std::string& msg, Args &&... args) {
  Logger::get().fatal(msg, std::forward<Args>(args)...);
}

}  // namespace cai::cailog