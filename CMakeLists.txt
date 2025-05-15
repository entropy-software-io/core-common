# Default allocator config
if ("${ENTROPY_CORE_CUSTOM_ALLOCATOR}" STREQUAL "")
    set (ENTROPY_CORE_CUSTOM_ALLOCATOR_INCLUDES "")
    set (ENTROPY_CORE_CUSTOM_ALLOCATOR "std::allocator<T>")
endif()

# Default string type config
if ("${ENTROPY_CORE_CUSTOM_STRING_INCLUDES}" STREQUAL "")
    set (ENTROPY_CORE_USE_CUSTOM_STRING_TYPE OFF)
else()
    set (ENTROPY_CORE_USE_CUSTOM_STRING_TYPE ON)
endif()

# Default vector type config
if ("${ENTROPY_CORE_CUSTOM_VECTOR_INCLUDES}" STREQUAL "")
    set (ENTROPY_CORE_USE_CUSTOM_VECTOR_TYPE OFF)
else()
    set (ENTROPY_CORE_USE_CUSTOM_VECTOR_TYPE ON)
endif()

# Default map type config
if ("${ENTROPY_CORE_CUSTOM_MAP_INCLUDES}" STREQUAL "")
    set (ENTROPY_CORE_USE_CUSTOM_MAP_TYPE OFF)
else()
    set (ENTROPY_CORE_USE_CUSTOM_MAP_TYPE ON)
endif()

# Default function type config
if ("${ENTROPY_CORE_CUSTOM_FUNCTION}" STREQUAL "")
    set (ENTROPY_CORE_USE_CUSTOM_FUNCTION_TYPE OFF)
    set (ENTROPY_CORE_CUSTOM_FUNCTION_INCLUDES "")
    set (ENTROPY_CORE_CUSTOM_FUNCTION "std::function<T>")
else()
    set (ENTROPY_CORE_USE_CUSTOM_FUNCTION_TYPE ON)
endif()

# Configure allocator and containers
configure_file(Config/AllocatorTraits.h.in Include/Entropy/Core/Details/AllocatorTraits.h)
configure_file(Config/StringOps.h.in Include/Entropy/Core/Details/StringOps.h)
configure_file(Config/VectorOps.h.in Include/Entropy/Core/Details/VectorOps.h)
configure_file(Config/MapOps.h.in Include/Entropy/Core/Details/MapOps.h)
configure_file(Config/FunctionTraits.h.in Include/Entropy/Core/Details/FunctionTraits.h)

set(CORE_COMMON_SRC "Src/Log.cpp")
add_library(entropy-core-common OBJECT ${CORE_COMMON_SRC})
add_library(entropy::core::common ALIAS entropy-core-common)

target_include_directories(entropy-core-common PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/Include>
)

if (NOT "${ENTROPY_CORE_EXTRA_INCLUDE_DIRECTORIES}" STREQUAL "")
    target_include_directories(entropy-core-common PUBLIC ${ENTROPY_CORE_EXTRA_INCLUDE_DIRECTORIES})
endif()

if (NOT "${ENTROPY_CORE_EXTRA_LINK_LIBRARIES}" STREQUAL "")
    target_link_libraries(entropy-core-common PUBLIC ${ENTROPY_CORE_EXTRA_LINK_LIBRARIES})
endif()
