cmake_minimum_required(VERSION 3.17)

project(CS202_Project)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "C:/Users/willg/source/repos/vcpkg/installed/x86-windows/share/sfml")#added to make code work on william's pc

set(SFML_DIR "C:/Users/Chris/source/repos/vcpkg/installed/x86-windows/share/sfml") #added to make code work on chris's pc

set(SFML_DIR "C:/vcpkg-master/installed/x86-windows/share/sfml")

add_executable(CS202_Project main.cpp)

find_package(SFML COMPONENTS graphics audio CONFIG REQUIRED)

target_link_libraries(CS202_Project sfml-graphics sfml-audio)
