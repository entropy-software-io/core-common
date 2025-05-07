set(CORE_COMMON_SRC "Src/Log.cpp")
add_library(entropy-core-common OBJECT ${CORE_COMMON_SRC})
add_library(entropy::core::common ALIAS entropy-core-common)

target_include_directories(entropy-core-common PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
)
