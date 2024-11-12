set(component binary)

add_library(${component} STATIC "")

set_property(TARGET ${component}
    PROPERTY PUBLIC_HEADER
    bitstream.hpp
    dynamic_library_loader.hpp
    reader.hpp
)

target_sources(${component}
    PRIVATE
    bitstream.hpp
    dynamic_library_loader.hpp
    dynamic_library_loader.cpp
    reader.hpp
)

target_include_directories(${component} PRIVATE "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(${component} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")
