cmake_minimum_required(VERSION 3.20)
project(hw5)

set(CMAKE_CXX_STANDARD 14)

ADD_CUSTOM_COMMAND(
        COMMENT "Generating Scanner.cpp"
        SOURCE CMinus.l
        OUTPUT ../Scanner.cpp
        COMMAND flex -o ../Scanner.cpp ../CMinus.l
        DEPENDS CMinus.l
)

ADD_CUSTOM_COMMAND(
        OUTPUT ../Parser.cpp ../Parser.hpp
        COMMAND bison -d -o../Parser.cpp ../CMinus.y
        DEPENDS CMinus.l CMinus.y
        COMMENT "Generating Parser.cpp and Parser.hpp"
)

add_executable(hw5 Scanner.cpp common.h Parser.cpp TreeNode.cpp treeParser.cpp treeParser.h variables.cpp variables.h functions.cpp functions.h main.cpp generator.cpp generator.h)