cmake_minimum_required(VERSION 3.8)
project(Ace)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES ../Sources/main.cpp ../Sources/Player.cpp ../Sources/Token.cpp ../Sources/GameEngine.cpp ../Headers/Player.h ../Headers/Token.h ../Headers/GameEngine.h)
add_executable(Ace ${SOURCE_FILES})