#pragma once

#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

struct CliOptions {
  std::string search_query;
  std::string order_query;
  std::vector<std::string> platform_query;
  bool all_platforms = false;
  bool show_version = false;
  bool echo = false;
  bool has_search = false;
  bool has_search_orders = false;
};

// clang-format off
const std::unordered_set<std::string_view> VALID_PLATFORMS =
  {
    "pc", 
    "xbox", 
    "ps4", 
    "switch"
  };
// clang-format on

void echoArgs(int argc, char *argv[]);
CliOptions processArgs(int argc, char *argv[]);
