#pragma once

#include <nlohmann/json.hpp>

using json = nlohmann::json;

void printSearch(const json &data);
void printOrders(const json &data);
