#include "core/market_api.h"

#include <cpr/api.h>
#include <cpr/cprtypes.h>
#include <cpr/response.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include <string>

using json = nlohmann::json;

// TODO: Handle invalid response
// TODO: Sort json array. Needs to somehow be processed out of a json array so
// that items are not printed per platform
constexpr const char *MARKET_URL = "https://api.warframe.market/v1";

json searchItem(const std::string &query) {
  cpr::Url url = std::string(MARKET_URL) + "/items/" + query;
  cpr::Response r = cpr::Get(url);
  json data = json::parse(r.text);
  return data;
}

// TODO: Use threads for this:
json searchItemOrders(const std::string &query,
                      const std::vector<std::string> &platformQuery) {
  json data = json::array();
  for (const auto &platform : platformQuery) {
    cpr::Url url = std::string(MARKET_URL) + "/items/" + query + "/orders";
    cpr::Response r = cpr::Get(url, cpr::Header{{"Platform", platform}});
    data.push_back(json::parse(r.text));
  }
  return data;
}
