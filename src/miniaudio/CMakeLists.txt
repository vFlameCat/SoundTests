add_library(miniaudio miniaudio.cpp)

target_compile_options(miniaudio PRIVATE -Wno-conversion -Wno-float-equal -Wno-cast-qual)