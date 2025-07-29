#include "core/market_api.h"

#include <cpr/api.h>
#include <cpr/cprtypes.h>
#include <cpr/error.h>
#include <cpr/response.h>
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include <format>
#include <stdexcept>
#include <string>

using json = nlohmann::json;

void handleErrors(const cpr::Response r);

// TODO: Sort json array. Needs to somehow be processed out of a json array so
// that items are not printed per platform
constexpr const char *MARKET_URL = "https://api.warframe.market/v1";

json searchItem(const std::string &query) {
  cpr::Url url = std::string(MARKET_URL) + "/items/" + query;
  cpr::Response r = cpr::Get(url);
  handleErrors(r);
  json data = json::parse(r.text);
  return data;
}

json searchItemOrders(const std::string &query,
                      const std::vector<std::string> &platformQuery) {
  std::vector<cpr::AsyncResponse> container{};
  for (const auto &platform : platformQuery) {
    cpr::Url url = std::string(MARKET_URL) + "/items/" + query + "/orders";
    container.emplace_back(
        cpr::GetAsync(url, cpr::Header{{"Platform", platform}}));
  }
  json data = json::array();
  for (cpr::AsyncResponse &ar : container) {
    cpr::Response r = ar.get();
    handleErrors(r);
    data.push_back(json::parse(r.text));
  }
  return data;
}

void handleErrors(const cpr::Response r) {
  if (r.error.code != cpr::ErrorCode::OK) {
    throw std::runtime_error(
        std::format("Network error has occured: {}", r.error.message));
  }

  if (r.status_code != 200) {
    switch (r.status_code) {
    case 404:
      throw std::runtime_error("Status code 404 was returned, item not found. "
                               "TIP: Check the name of the item, is it in the "
                               "following format? \n \"rubico_prime_set\"");
    default:
      throw std::runtime_error(
          std::format("Error code {} was returned", r.status_code));
      break;
    }
  }
}
