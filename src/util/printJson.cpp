#include "util/printJson.h"

#include <format>
#include <iostream>
#include <string>

// TODO: Remove the existance checks for json keys and perform this validation
// in market_api.cpp
void printSearch(const json &data) {
  const json &items = data["payload"]["item"]["items_in_set"];
  std::cout << "Items in set: \n";
  for (const json &item : items) {
    std::cout << "Search Results for "
              << item["en"]["item_name"].get<std::string>() << '\n';

    if (item["en"].contains("description")) {
      std::string description = item["en"]["description"].get<std::string>();
      std::cout << '\t' << "Description: " << description << '\n';
    }

    if (item.contains("ducats")) {
      int ducats{item["ducats"].get<int>()};
      std::cout << '\t' << "Ducats: " << ducats << '\n';
    }

    if (item.contains("vaulted")) {
      bool vaulted = item["vaulted"].get<bool>();
      std::cout << '\t' << "Vaulted: " << (vaulted ? "yes" : "no") << '\n';
    }

    if (item["en"].contains("wiki_link")) {
      std::string wiki = item["en"]["wiki_link"].get<std::string>();
      std::cout << '\t' << "Warframe Wiki: " << wiki << '\n';
    }

    std::cout << '\n';
  }
}

void printOrders(const json &data) {
  constexpr int width = 15;
  constexpr int maxStringLength = 10;
  std::cout << std::format("{:>{}}", "Platinum", width)
            << std::format("{:>{}}", "Quantity", width)
            << std::format("{:>{}}", "User Name", width)
            << std::format("{:>{}}", "Status", width)
            << std::format("{:>{}}", "Platform", width) << '\n';

  for (const auto &platform_data : data) {
    const auto &items = platform_data["payload"]["orders"];
    for (const auto &item : items) {
      if (item["user"]["status"] != "offline") {
        int platinum = item["platinum"].get<int>();
        int quantity = item["quantity"].get<int>();
        std::string name = item["user"]["ingame_name"].get<std::string>();
        std::string status = item["user"]["status"].get<std::string>();
        std::string platform = item["user"]["platform"].get<std::string>();

        if (name.length() > maxStringLength) {
          name = name.substr(0, maxStringLength) + "...";
        }

        std::cout << std::format("{:>{}}", platinum, width)
                  << std::format("{:>{}}", quantity, width)
                  << std::format("{:>{}}", name, width)
                  << std::format("{:>{}}", status, width)
                  << std::format("{:>{}}", platform, width) << '\n';
      }
    }
  }
}
