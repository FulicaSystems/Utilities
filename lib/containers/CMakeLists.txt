set(component containers)

add_library(${component} STATIC "")

set_property(TARGET ${component}
    PROPERTY PUBLIC_HEADER
    circular_buffer.hpp
    queue.hpp
    rawtext.hpp
)

target_sources(${component}
    PRIVATE
    circular_buffer.hpp
    queue.hpp
    rawtext.hpp
    rawtext.cpp
)

target_include_directories(${component} PRIVATE "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(${component} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")
