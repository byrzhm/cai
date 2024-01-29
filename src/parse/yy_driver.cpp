#include <cassert>
#include <cctype>
#include <fstream>

#include "parse/yy_driver.h"

namespace yy {

auto YYDriver::parse() -> int {
  location_.initialize(&filename_);
  scan_begin();
  YYParser parse(*this);
  parse.set_debug_level(
      static_cast<YYParser::debug_level_type>(trace_parsing_));
  int res = parse();
  scan_end();
  return res;
}

auto YYDriver::parse(const std::string &filename) -> int {
  filename_ = filename;
  return parse();
}

} // namespace yy
