# Please note that compiling is not necessary for this library, please refer to the readme for more information

cmake_minimum_required(VERSION 3.20)

project(RaylibGuiCreator)

set(CMAKE_CXX_STANDARD 17) # Use C++ 17

if (WIN32)
	find_package(raylib CONFIG REQUIRED) # For VCPKG
else()
	find_package(raylib REQUIRED) # For Linux/Unix
endif()

file(GLOB RAYLIB_SOURCES ${CMAKE_CURRENT_LIST_DIR}/*.cpp)

add_executable(RaylibGuiCreator ${RAYLIB_SOURCES})
target_include_directories(RaylibGuiCreator PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(RaylibGuiCreator PRIVATE ${raylib_LIBRARIES})