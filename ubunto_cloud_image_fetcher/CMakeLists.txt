cmake_minimum_required(VERSION 3.10)
project(UbuntuCloudImageInfo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add external dependencies
find_package(CURL REQUIRED)
find_package(nlohmann_json 3.2.0 REQUIRED)

# Add source files
set(SOURCES
    src/main.cpp
    src/CloudImageInfo.cpp
    src/SimplestreamsParser.cpp
)

# Add header files
set(HEADERS
    include/CloudImageInfo.h
    include/SimplestreamsParser.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl nlohmann_json::nlohmann_json)