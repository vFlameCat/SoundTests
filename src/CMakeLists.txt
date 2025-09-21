target_sources(${MAIN_TARGET} PRIVATE main.cpp)

add_subdirectory(SoundPlayer)
target_include_directories(${MAIN_TARGET} PRIVATE SoundPlayer)

add_subdirectory(miniaudio)
target_link_libraries(${MAIN_TARGET} PRIVATE miniaudio)
target_include_directories(${MAIN_TARGET} PRIVATE miniaudio)