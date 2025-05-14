# Default allocator config
if ("${ENTROPY_CORE_DEFAULT_ALLOCATOR}" STREQUAL "")
    set (ENTROPY_CORE_DEFAULT_ALLOCATOR_INCLUDES "")
    set (ENTROPY_CORE_DEFAULT_ALLOCATOR "std::allocator<T>")
endif()

# Default string type config
if ("${ENTROPY_CORE_CUSTOM_STRING_INCLUDES}" STREQUAL "")
    set (ENTROPY_CORE_USE_CUSTOM_STRING_TYPE OFF)
else()
    set (ENTROPY_CORE_USE_CUSTOM_STRING_TYPE ON)
endif()

# Configure allocator and containers
configure_file(Config/AllocatorTraits.h.in Include/Entropy/Core/Details/AllocatorTraits.h)
configure_file(Config/StringOps.h.in Include/Entropy/Core/Details/StringOps.h)

set(CORE_COMMON_SRC "Src/Log.cpp")
add_library(entropy-core-common OBJECT ${CORE_COMMON_SRC})
add_library(entropy::core::common ALIAS entropy-core-common)

target_include_directories(entropy-core-common PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Include>
)
