set(component lib)

add_library(${component} INTERFACE "")
add_library(Utilities ALIAS ${component})

set_property(TARGET ${component}
    PROPERTY PUBLIC_HEADER
    checkleak.hpp
    derived.hpp
    property.hpp
    singleton.hpp
    time_manager.hpp
    input_manager.hpp
)

target_include_directories(${component} PRIVATE "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(${component} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")

add_subdirectory(ai)
add_subdirectory(binary)
add_subdirectory(containers)
add_subdirectory(multithread)

install(TARGETS ${component})
install(
    DIRECTORY internal/
    DESTINATION include
    FILES_MATCHING
    PATTERN *.h
    PATTERN *.hpp
    PATTERN *.inl
)