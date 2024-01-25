#include <cassert>
#include <cctype>
#include <fstream>

#include "parse/yy_driver.h"

namespace yy {

auto YYDriver::parse(const std::string &filename) -> int {
  filename_ = filename;
  location_.initialize(&filename_);
  scan_begin();
  YYParser parse(*this);
  parse.set_debug_level(
      static_cast<YYParser::debug_level_type>(trace_parsing_));
  int res = parse();
  scan_end();
  return res;
}

} // namespace yy
