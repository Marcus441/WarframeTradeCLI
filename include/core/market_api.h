#pragma once

#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

json searchItem(std::string &query);
json searchItemOrders(std::string &query);
