// main file;
#include "cli/parser.h"

#include "core/market_api.h"
#include "util/echoArgs.h"

#include <exception>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

  CliOptions options;
  // args are processed here
  try {
    options = processArgs(argc, argv);
  } catch (const std::exception &e) {
    std::cerr << e.what();
    return 1;
  }
  // args processing finished

  if (options.show_version) {
    std::cout << "Version: 0.0.1";
    return 0;
  }
  if (options.echo) {
    echoArgs(argc, argv);
  }
  if (options.has_search) {
    if (!options.search_query.empty()) {
      searchItem(options.search_query);
    }
  }
  if (options.has_search_orders) {
    if (!options.search_query.empty()) {
      searchItemOrders(options.search_query);
    }
  }

  return 0;
}
