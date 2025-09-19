cmake_minimum_required(VERSION 3.28)

project(SoundTests)


include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main)
target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main PRIVATE SFML::Graphics)


add_subdirectory(src)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/res/7NA.mp3  ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/res/ComicSansMS.ttf  ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
