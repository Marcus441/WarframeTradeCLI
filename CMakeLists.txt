cmake_minimum_required(VERSION 3.31.7)

project(wftcli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set third_party for FetchContent
set(FETCHCONTENT_BASE_DIR ${CMAKE_SOURCE_DIR}/third_party)

include(FetchContent)

FetchContent_Declare(
  cpr
  GIT_REPOSITORY https://github.com/libcpr/cpr.git
  GIT_TAG        1.12.0
)
FetchContent_Declare(
  json 
  URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)

FetchContent_MakeAvailable(cpr)
FetchContent_MakeAvailable(json)

# Build executable
add_executable(${PROJECT_NAME}
  src/main.cpp
  src/cli/parser.cpp
  src/core/market_api.cpp
  src/util/echoArgs.cpp
  src/util/printJson.cpp
)

# Include paths 
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)
# Compiler flags
target_compile_options(${PROJECT_NAME} PRIVATE -pedantic -Wall -Wextra)

# Include paths for third party libraries 
get_target_property(CPR_INCLUDE_DIR cpr::cpr INTERFACE_INCLUDE_DIRECTORIES)
get_target_property(JSON_INCLUDE_DIR nlohmann_json::nlohmann_json INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(${PROJECT_NAME}
  SYSTEM PRIVATE
    ${CPR_INCLUDE_DIR}
    ${JSON_INCLUDE_DIR}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE cpr::cpr)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
