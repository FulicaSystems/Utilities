set(component ai)

add_library(${component} STATIC "")

set_property(TARGET ${component}
    PROPERTY PUBLIC_HEADER
    activation.hpp
    perceptron.hpp
)

target_sources(${component}
    PRIVATE
    activation.hpp
    activation.cpp
    perceptron.hpp
    perceptron.cpp
)

target_include_directories(${component} PRIVATE "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(${component} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")

add_subdirectory(neural_network)