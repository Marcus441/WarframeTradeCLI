#include "cli/parser.h"

#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>

void echoArgs(int argc, char *argv[]) {
  std::cout << "argc: " << argc << '\n';
  for (int i = 0; i < argc; ++i) {
    std::cout << "argv[" << i << "]: " << argv[i] << '\n';
  }
}

void processArgs(int argc, char *argv[]) {
  std::unordered_map<std::string, std::function<void(int &)>> argMap = {

      {"-v",
       [&](int &) {
         std::cout << "version 0.0.1\n";
         exit(0);
       }},
      {"--version", [&](int &i) { argMap["-v"](i); }},
      {"-e",
       [&](int &) {
         echoArgs(argc, argv);
         exit(0);
       }},
      {"--echo", [&](int &i) { argMap["-e"](i); }},
      {"-s",
       [&](int &i) {
         if (i + 1 >= argc) {
           std::cout << "Missing argument for -s/--search" << '\n';
           exit(1);
         }
         std::string query = argv[i + 1];
         std::cout << "Searching for: " << query << ".\n";
         exit(0);
       }}

  };

  for (int i = 1; i < argc; ++i) {
    std::string userArgString = argv[i];
    auto currentArg = argMap.find(userArgString);
    if (currentArg != argMap.end()) {
      currentArg->second(i);
    } else {
      std::cerr << "Unknown argument: " << userArgString << ".\n";
    }
  }
}
