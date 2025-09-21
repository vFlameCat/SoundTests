cmake_minimum_required(VERSION 3.28)

project(SoundTests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(MAIN_TARGET "main")
add_executable(${MAIN_TARGET})


include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

target_link_libraries(${MAIN_TARGET} PRIVATE SFML::Graphics)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter \
                                        -Wshadow -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal \
                                        -Winline -Wmissing-include-dirs -Weffc++ -Wmain -Wcast-qual \
                                        -Wconversion -Wctor-dtor-privacy -Wformat-security -Wlogical-op \
                                        -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith \
                                        -Wstrict-aliasing -Wstrict-null-sentinel -Wwrite-strings -Wno-comment")
                                        
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fno-omit-frame-pointer -fsanitize=address")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -mavx2 -pipe -DNDEBUG")


#copy resources
set(RESOURCES_FOLDER "res")
file(GLOB_RECURSE RESOURCE_FILES "${RESOURCES_FOLDER}/*")
foreach(RES_FILE ${RESOURCE_FILES})

    string(REPLACE "${CMAKE_SOURCE_DIR}/" "" RELATIVE_PATH ${RES_FILE})
    set(DEST_FILE "${CMAKE_BINARY_DIR}/${RELATIVE_PATH}")
    
    configure_file(${RES_FILE} ${DEST_FILE} COPYONLY)

endforeach()


add_subdirectory(src)
