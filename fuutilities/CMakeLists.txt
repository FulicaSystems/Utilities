set(component fuutilities)

add_library(${component} INTERFACE "")
add_library(FuUtilities ALIAS ${component})

option(UTILITIES_BUILD_AI_UTILS "build AI utilities" ON)
option(UTILITIES_BUILD_BINARY_UTILS "build binary utilities" ON)
option(UTILITIES_BUILD_CONTAINERS_UTILS "build containers utilities" ON)
option(UTILITIES_BUILD_MULTITHREAD_UTILS "build multithread utilities" ON)

set_property(TARGET ${component}
    PROPERTY PUBLIC_HEADER
    checkleak.hpp
    derived.hpp
    property.hpp
    singleton.hpp
    time_manager.hpp
    input_manager.hpp
)

target_include_directories(${component} INTERFACE "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(${component} INTERFACE "${CMAKE_CURRENT_LIST_DIR}/..")

if (UTILITIES_BUILD_AI_UTILS)
    add_subdirectory(ai)
    target_link_libraries(${component}
        INTERFACE ai
    )
endif()
if (UTILITIES_BUILD_BINARY_UTILS)
    add_subdirectory(binary)
    target_link_libraries(${component}
        INTERFACE binary
    )
endif()
if (UTILITIES_BUILD_CONTAINERS_UTILS)
    add_subdirectory(containers)
    target_link_libraries(${component}
        INTERFACE containers
    )
endif()
if (UTILITIES_BUILD_MULTITHREAD_UTILS)
    add_subdirectory(multithread)
    target_link_libraries(${component}
        INTERFACE multithread
    )
endif()


install(TARGETS ${component})
install(
    DIRECTORY internal/
    DESTINATION include
    FILES_MATCHING
    PATTERN *.h
    PATTERN *.hpp
    PATTERN *.inl
)