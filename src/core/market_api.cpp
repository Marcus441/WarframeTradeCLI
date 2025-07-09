#include "core/market_api.h"

#include "cpr/api.h"
#include "cpr/cprtypes.h"
#include "cpr/response.h"
#include "nlohmann/json_fwd.hpp"

#include <nlohmann/json.hpp>

#include <iostream>
#include <string>

using json = nlohmann::json;

constexpr const char *MARKET_URL = "https://api.warframe.market/v1";

// TODO: change return type of these to json and separate console output logic

void searchItem(std::string query) {
  std::cout << "Searching for: " << query << '\n';
  cpr::Response r =
      cpr::Get(cpr::Url{std::string(MARKET_URL) + "/items/" + query});
  std::cout << "Status: " << r.status_code;
  json data = r.text;
  std::cout << data.dump();
}

void searchItemOrders(std::string query) {
  std::cout << "Searching orders for: " << query << '\n';
  cpr::Response r = cpr::Get(
      cpr::Url{std::string(MARKET_URL) + "/items/" + query + "/orders"});
  std::cout << "Status: " << r.status_code;
  json data = r.text;
  std::cout << data.dump();
}
