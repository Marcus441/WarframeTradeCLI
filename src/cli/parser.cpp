#include "cli/parser.h"

#include <functional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>

CliOptions processArgs(int argc, char *argv[]) {
  CliOptions options;
  std::unordered_map<std::string, std::function<void(int &)>> argMap = {

      {"-v", [&](int &) { options.show_version = true; }},
      {"--version", [&](int &i) { argMap["-v"](i); }},
      {"--echo", [&](int &) { options.echo = true; }},
      {"-s",
       [&](int &i) {
         if (i + 1 >= argc || argv[i + 1] == nullptr ||
             std::string(argv[i + 1]).starts_with('-')) {
           throw std::runtime_error("Missing argument for -s/--search");
         }

         std::string next = argv[i + 1];
         if (next.empty()) {
           throw std::runtime_error("Null search query not allowed");
         }

         options.has_search = true;
         options.search_query = argv[++i];
       }},
      {"--search", [&](int &i) { argMap["-s"](i); }},
      {"-o",
       [&](int &i) {
         if (i + 1 >= argc || argv[i + 1] == nullptr ||
             std::string(argv[i + 1]).starts_with('-')) {
           throw std::runtime_error("Missing argument for -o/--orders");
         }

         std::string next = argv[i + 1];
         if (next.empty()) {
           throw std::runtime_error("Null search query not allowed");
         }

         options.has_search_orders = true;
         options.order_query = argv[++i];
       }},
      {"--orders", [&](int &i) { argMap["-o"](i); }},
      {"--platforms=",
       [&](int &i) {
         std::string argument = argv[i];
         std::string values =
             argument.substr(std::string("--platforms=").length());

         std::istringstream platforms{values};
         std::string token;
         while (std::getline(platforms, token, ',')) {
           if (VALID_PLATFORMS.contains(token)) {
             options.platform_query.push_back(token);
           } else {
             throw std::runtime_error("Invalid platform: " + token);
           }
         }
       }}

  };

  for (int i = 1; i < argc; ++i) {
    std::string currentArg = argv[i];
    auto it = argMap.find(currentArg);

    // check for --platforms=<value> case
    if (currentArg.starts_with("--platforms=")) {
      it = argMap.find("--platforms=");
    }

    if (it != argMap.end()) {
      it->second(i);
    } else {
      throw std::runtime_error("Unknown argument: " + currentArg);
    }
  }

  return options;
}
