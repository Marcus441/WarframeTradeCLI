#include "util/printJson.h"

#include <iostream>
#include <string>

void printSearch(json &data) {
  const json &items = data["payload"]["item"]["items_in_set"];
  std::cout << "Items in set: \n";
  for (const json &item : items) {
    std::cout << "Item name: " << item["en"]["item_name"] << '\n';
    if (item["en"].contains("description"))
      std::cout << '\t' << "Description: " << item["en"]["description"] << '\n';
    if (item.contains("ducats"))
      std::cout << '\t' << "Ducats: " << item["ducats"] << '\n';
    if (item.contains("vaulted"))
      std::cout << '\t' << "Vaulted: " << item["vaulted"] << '\n';
    if (item["en"].contains("wiki_link")) {
      std::cout << '\t' << "Warframe Wiki: " << item["en"]["wiki_link"] << '\n';
    }
    std::cout << '\n';
  }
}

void printOrders(json &data) {}
