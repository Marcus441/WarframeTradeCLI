#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

void printSearch(json &data);
void printOrders(json &data);
