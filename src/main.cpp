// main file;
#include "cli/parser.h"

#include "core/market_api.h"
#include "util/echoArgs.h"
#include "util/printJson.h"

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
    return 0;
  }
  if (!options.search_query.empty() || !options.order_query.empty()) {
    if (options.has_search) {
      json result = searchItem(options.search_query);
      printSearch(result);
    }
    if (options.has_search_orders) {
      std::cout << searchItemOrders(options.order_query).dump(4);
    }
    return 0;
  }

  return 0;
}
