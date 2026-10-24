cmake_minimum_required(VERSION 3.22)
project(SidechainReceiver LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    dpf
    GIT_REPOSITORY https://github.com/DISTRHO/DPF/
    GIT_TAG 4238e1c7f0351bbe488d79f0899c540543ac7583 # latest commit on the main branch (at the time of writing)
)
FetchContent_MakeAvailable(dpf)

dpf_add_plugin(${PROJECT_NAME}
    TARGETS vst3
    FILES_DSP src/plugin.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC src)

