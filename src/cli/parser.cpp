#include "cli/parser.h"

#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>

CliOptions processArgs(int argc, char *argv[]) {
  CliOptions options;
  std::unordered_map<std::string, std::function<void(int &)>> argMap = {

      {"-v", [&](int &) { options.show_version = true; }},
      {"--version", [&](int &i) { argMap["-v"](i); }},
      {"-e", [&](int &) { options.echo = true; }},
      {"--echo", [&](int &i) { argMap["-e"](i); }},
      {"-s",
       [&](int &i) {
         if (i + 1 >= argc || argv[i + 1] == nullptr) {
           throw std::runtime_error("Missing argument for -s/--search");
         }
         options.has_search = true;
         options.search_query = argv[++i];
       }},
      {"-o",
       [&](int &i) {
         if (i + 1 >= argc || argv[i + 1] == nullptr) {
           throw std::runtime_error("Missing argument for -o/--orders");
         }
         options.has_search_orders = true;
         options.search_query = argv[++i];
       }},
      {"--orders", [&](int &i) { argMap["-o"](i); }}

  };

  for (int i = 1; i < argc; ++i) {
    std::string currentArg = argv[i];
    auto it = argMap.find(currentArg);
    if (it != argMap.end()) {
      it->second(i);
    } else {
      throw std::runtime_error("Unknown argument: " + currentArg);
    }
  }

  return options;
}
