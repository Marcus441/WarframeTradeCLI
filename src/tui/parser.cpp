#include "tui/parser.h"

#include <cstddef>
#include <cstdlib>
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "core/market_api.h"

void processTuiArgs(std::string &input, TuiOptions &commandState) {
  std::unordered_map<std::string, std::function<void()>> commandMap = {
      {"search", [&]() {
         constexpr std::string_view cmd = "search";
         std::size_t pos = input.find(cmd) + cmd.length();
         std::string searchQuery = input.substr(pos);
         if (searchQuery.empty()) {
           throw std::runtime_error("Missing argument for search");
         }
         commandState.has_search = true;
         commandState.search_query = searchQuery;
       }}};

  std::size_t pos = input.find(' ');
  std::string command = input.substr(0, pos);
  auto it = commandMap.find(command);
  if (it != commandMap.end()) {
    it->second();
  } else {
    throw std::runtime_error("Unknown argument: " + command);
  }
}

bool handleTuiArgs(TuiOptions &state) {
  if (!state.search_query.empty() || !state.order_query.empty()) {
    // make pc the default platform
    if (state.platform_query.empty()) {
      state.platform_query.emplace_back("pc");
    }
    if (state.has_search) {
      try {
        json result = searchItem(state.search_query);
        state.output = result.dump();
      } catch (const std::exception &e) {
        state.reset();
        return false;
      }
    }
    if (state.has_search_orders) {
      try {
        json result = searchItemOrders(state.order_query, state.platform_query);
        state.output = result.dump();
      } catch (const std::exception &e) {
        state.reset();
        return false;
      }
    }
    state.reset();
    return false;
  }
  state.reset();
  return true;
}
