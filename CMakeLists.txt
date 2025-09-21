cmake_minimum_required(VERSION 3.28)

project(SoundTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main)
target_link_libraries(main PRIVATE SFML::Graphics)


add_subdirectory(src)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -mavx2 -pipe -DNDEBUG")


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/res/7NA.mp3  ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/res/ComicSansMS.ttf  ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
