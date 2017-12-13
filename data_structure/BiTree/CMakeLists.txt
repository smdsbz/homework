cmake_minimum_required(VERSION 3.7)
project(BiTree)

set(CMAKE_C_STANDARD 11)

#set(SOURCE_FILES )
add_executable(BiTree main.c BiTree.c Stack.c BiTree.h MACROS.h Stack.h)
