#pragma once

#include <string>

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

  static auto get() -> Logger&;

  template <typename... Args>
  void trace(const std::string& msg, Args &&... args);

  template <typename... Args>
  void info(const std::string& msg, Args &&... args);

  template <typename... Args>
  void warn(const std::string& msg, Args &&... args);

  template <typename... Args>
  void error(const std::string& msg, Args &&... args);

  template <typename... Args>
  void fatal(const std::string& msg, Args &&... args);

  void set_log_level(LogLevel log_level);

private:
  LogLevel log_level_ = LogLevel::TRACE;
};

template <typename... Args>
void trace(const std::string& msg, Args &&... args) {
  Logger::get().trace(msg, std::forward(args)...);
}

template <typename... Args>
void info(const std::string& msg, Args &&... args) {
  Logger::get().info(msg, std::forward(args)...);
}

template <typename... Args>
void warn(const std::string& msg, Args &&... args) {
  Logger::get().warn(msg, std::forward(args)...);
}

template <typename... Args>
void error(const std::string& msg, Args &&... args) {
  Logger::get().error(msg, std::forward(args)...);
}

template <typename... Args>
void fatal(const std::string& msg, Args &&... args) {
  Logger::get().fatal(msg, std::forward(args)...);
}

}  // namespace cai::cailog