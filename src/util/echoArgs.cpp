#include "util/echoArgs.h"

#include <iostream>

void echoArgs(int argc, char *argv[]) {
  std::cout << "argc: " << argc << '\n';
  for (int i = 0; i < argc; ++i) {
    std::cout << "argv[" << i << "]: " << argv[i] << '\n';
  }
}
