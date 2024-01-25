#include "util/cai_log.h"
#include "driver/cai_driver.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <filesystem>

/**
 * See https://www.boost.org/doc/libs/1_58_0/doc/html/program_options.html
 */
namespace po = boost::program_options;

class CommandArgs {
public:
  static auto get() -> CommandArgs& {
    static CommandArgs instance;
    return instance;
  }

  bool emit_ir_ = false;
  int optimize_level_ = 0;
  std::string input_file_;
  std::string output_file_;
  std::string ir_file_;

private:
  CommandArgs() = default;
};

void parse_args(int argc, char **argv) {
  po::options_description desc("Allowed options");
  desc.add_options()
     ("help,h", "produce help message")
     ("emit-ir", "output IR file")
     ("output-file,o", po::value<std::string>(&CommandArgs::get().output_file_), "output file")
     ("input-file", po::value<std::string>(&CommandArgs::get().input_file_), "input file")
     ("optimize-level,O", po::value<int>(&CommandArgs::get().optimize_level_), "optimize level[0-1]");

  po::positional_options_description p;
  p.add("input-file", -1);

  po::variables_map vm;
  po::store(
      po::command_line_parser(argc, argv).options(desc).positional(p).run(),
      vm);
  po::notify(vm);

  if (vm.count("help") > 0) {
    std::cout << desc << std::endl;
    exit(0);
  }

  if (vm.count("emit-ir") > 0) {
    CommandArgs::get().emit_ir_ = true;
  }

  if (vm.count("input-file") == 0) {
    cailog::error("No input file specified.");
    exit(1);
  }

  if (vm.count("output-file") == 0) {
    std::filesystem::path input_path(CommandArgs::get().input_file_);
    std::string input_file_without_ext = input_path.stem().string();
    std::string input_file_ext = input_path.extension().string();

    if (!input_file_ext.empty()) {
      input_path.replace_extension(".s");
    } else {
      input_path += ".s";
    }

    CommandArgs::get().output_file_ = input_path.string();
  }

}

auto main(int argc, char **argv) -> int {
  parse_args(argc, argv);
  cai::CaiDriver driver;
  return 0;
}