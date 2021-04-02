cmake_minimum_required(VERSION 3.17)
project(CS202_Project)

set(CMAKE_CXX_STANDARD 20)

add_executable(CS202_Project main.cpp)

include_directories(headers C:/SFML/include)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake-build-debug/cmake_modules")
find_package(SFML COMPONENTS graphics audio REQUIRED)
if(SFML_FOUND)
    include_directories((${SFML_INCLUDE_DIR}))
    target_link_libraries(CS202_Project ${SFML_LIBRARIES})
endif()

