# The first line states the minimum CMake version to use with this project
# and is requires by CMake.
cmake_minimum_required(VERSION 3.0.0)
set(CMAKE_CXX_STANDARD 11)


# Set <PROJNAME> to be your project name. We set CXX (C++) here as the target language.
project(DS_Wet_2 VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_C_COMPILER "C:\\TDM-GCC-64\\bin\\gcc.exe")
set(CMAKE_CXX_COMPILER "C:\\TDM-GCC-64\\bin\\g++.exe")
# If you want to see "under the hood" of CMake, uncomment this:
set(CMAKE_VERBOSE_MAKEFILE ON)


# Define variables containing compiler flags for gcc
set(DS_FLAGS_DEBUG "-std=c++11 -DNDEBUG -Wall")
set(DS_FLAGS_RELEASE "${DS_FLAGS_DEBUG} -DNDEBUG")

# Set the flags for gcc
set(CMAKE_CPP_FLAGS ${DS_FLAGS_DEBUG})


# Add the names of your source files here
set(CPP_FILES ./ownTest.cpp ./library2.cpp ./PlayersManager.cpp ./Group.cpp ./Player.cpp)

add_executable(DS_Wet_2_Staff_Test ${CPP_FILES})