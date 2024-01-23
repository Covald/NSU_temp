cmake_minimum_required(VERSION 3.27)
project(Structure_programming_project_auth C)

set(CMAKE_C_STANDARD 23)

add_executable(Structure_programming_project_auth main.c
        hash.c
        hash.h
        user.c
        user.h
        AVL.c
        AVL.h
        menu.c
        menu.h
        dynamic_string.c
        dynamic_string.h
        settings.h
)
