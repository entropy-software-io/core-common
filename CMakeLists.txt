add_library(entropy-core-common INTERFACE)
add_library(entropy::core::common ALIAS entropy-core-common)

target_include_directories(entropy-core-common INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)
