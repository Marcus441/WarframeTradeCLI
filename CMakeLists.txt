cmake_minimum_required(VERSION 3.31.7)

project(wftcli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES}
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PRIVATE 
  cpr::cpr 
  nlohmann_json::nlohmann_json
)

target_compile_options(${PROJECT_NAME} PRIVATE -pedantic -Wall -Wextra)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
