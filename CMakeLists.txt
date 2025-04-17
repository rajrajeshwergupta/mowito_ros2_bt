cmake_minimum_required(VERSION 3.5)
project(robot_task)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(behaviortree_cpp_v3 REQUIRED)

add_executable(robot_task main.cpp)

target_link_libraries(robot_task behaviortree_cpp_v3)