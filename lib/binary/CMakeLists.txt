set(component binary)

add_library(${component} INTERFACE "")

set_property(TARGET ${component}
    PROPERTY PUBLIC_HEADER
    bitstream.hpp
    dynamic_library_loader.hpp
    reader.hpp
)

target_include_directories(${component} PRIVATE "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(${component} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")
