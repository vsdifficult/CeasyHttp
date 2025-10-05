# Project setup
cmake_minimum_required(VERSION 3.10)
project(CeasyHttp VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the library
add_library(ceasyhttp
    src/http_easy_reports.cpp
    src/http_easy_requests.cpp
)

# Include directories for the library
target_include_directories(ceasyhttp PUBLIC include)

# Add the example executable
add_executable(example examples/main.cpp)

# Link the library to the example
target_link_libraries(example PRIVATE ceasyhttp)
