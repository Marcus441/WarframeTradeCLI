#pragma once

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

json searchItem(const std::string &query);
json searchItemOrders(const std::string &query,
                      const std::vector<std::string> &platforms);
