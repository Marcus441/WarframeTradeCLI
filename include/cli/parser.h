#pragma once

#include <string>

struct CliOptions {
  std::string search_query;
  bool show_version = false;
  bool echo = false;
  bool has_search = false;
};

void echoArgs(int argc, char *argv[]);
CliOptions processArgs(int argc, char *argv[]);
