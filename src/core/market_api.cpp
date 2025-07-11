#include "core/market_api.h"

#include <cpr/api.h>
#include <cpr/cprtypes.h>
#include <cpr/response.h>
#include <nlohmann/json.hpp>

#include <string>

using json = nlohmann::json;

constexpr const char *MARKET_URL = "https://api.warframe.market/v1";

// TODO: change return type of these to json and separate console output logic

json searchItem(std::string &query) {
  // std::cout << "Searching for: " << query << '\n';
  cpr::Response r =
      cpr::Get(cpr::Url{std::string(MARKET_URL) + "/items/" + query});
  // std::cout << "Status: " << r.status_code << '\n';
  json data = json::parse(r.text);
  return data;
}

json searchItemOrders(std::string &query) {
  // std::cout << "Searching orders for: " << query << '\n';
  cpr::Response r = cpr::Get(
      cpr::Url{std::string(MARKET_URL) + "/items/" + query + "/orders"});
  // std::cout << "Status: " << r.status_code << '\n';
  json data = json::parse(r.text);
  return data;
}
