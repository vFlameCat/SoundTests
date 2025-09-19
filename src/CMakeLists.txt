target_sources(main PRIVATE main.cpp)

add_subdirectory(SoundPlayer)
target_include_directories(main PRIVATE SoundPlayer)

add_subdirectory(miniaudio)
target_link_libraries(main PRIVATE miniaudio)
target_include_directories(main PRIVATE miniaudio)