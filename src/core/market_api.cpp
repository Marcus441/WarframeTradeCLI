#include "core/market_api.h"

#include <cpr/api.h>
#include <cpr/cprtypes.h>
#include <cpr/response.h>
#include <nlohmann/json.hpp>

#include <string>

using json = nlohmann::json;

constexpr const char *MARKET_URL = "https://api.warframe.market/v1";

json searchItem(std::string &query) {
  cpr::Response r =
      cpr::Get(cpr::Url{std::string(MARKET_URL) + "/items/" + query});
  json data = json::parse(r.text);
  return data;
}

json searchItemOrders(std::string &query) {
  cpr::Response r = cpr::Get(
      cpr::Url{std::string(MARKET_URL) + "/items/" + query + "/orders"});
  json data = json::parse(r.text);
  return data;
}
