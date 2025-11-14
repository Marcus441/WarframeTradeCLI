#pragma once

#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

// clang-format off
const std::unordered_set<std::string_view> VALID_PLATFORMS =
  {
    "pc", 
    "xbox", 
    "ps4", 
    "switch"
  };
// clang-format on

struct TuiOptions {
  std::string search_query;
  std::string order_query;
  std::vector<std::string> platform_query;
  std::string output = "";
  bool all_platforms = false;
  bool has_search = false;
  bool has_search_orders = false;

  void reset() {
    this->search_query = "";
    this->order_query = "";
    this->platform_query = {};
    this->all_platforms = false;
    this->has_search = false;
    this->has_search_orders = false;
  };

  void clearOutput() { output = ""; };
};

void processTuiArgs(std::string &input, TuiOptions &commandState);
bool handleTuiArgs(TuiOptions &state);
