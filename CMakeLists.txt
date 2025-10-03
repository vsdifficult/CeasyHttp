cmake_minimum_required(VERSION 3.10)

project(CeasyHttp)

# Add the library
add_library(CeasyHttp src/http_easy_requests.cpp)

# Make the "include" directory available to the library and other projects
target_include_directories(CeasyHttp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Add an example executable
add_executable(example examples/main.cpp)

# Link the example with the library
target_link_libraries(example CeasyHttp)