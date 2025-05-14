# Default allocator and container values
if ("${ENTROPY_CORE_DEFAULT_ALLOCATOR}" STREQUAL "")
    set (ENTROPY_CORE_DEFAULT_ALLOCATOR_INCLUDES "")
    set (ENTROPY_CORE_DEFAULT_ALLOCATOR "std::allocator<T>")
endif()

# Configure allocator and containers
configure_file(Config/AllocatorTraits.h.in Include/Entropy/Core/Details/AllocatorTraits.h)

set(CORE_COMMON_SRC "Src/Log.cpp")
add_library(entropy-core-common OBJECT ${CORE_COMMON_SRC})
add_library(entropy::core::common ALIAS entropy-core-common)

target_include_directories(entropy-core-common PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Include>
)
