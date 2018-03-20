cmake_minimum_required(VERSION 3.8)
project(SportSystem_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        cmake-build-debug/SportSystem.cbp
        cmake-build-debug/SportSystem.exe
        CMakeLists.txt

        Inked微信图片_20180311220616_LI.jpg

        main.c
        Liner_List_Operation.h file_operation.h)

add_executable(SportSystem_2 ${SOURCE_FILES} main.c)