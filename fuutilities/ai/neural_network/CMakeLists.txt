set(component neural_network)

add_library(${component} STATIC "")

set_property(TARGET ${component}
    PROPERTY PUBLIC_HEADER
    dqlmodel.hpp
    mlpmodel.hpp
)

target_sources(${component}
    PRIVATE
    dqlmodel.hpp
    mlpmodel.hpp
    mlpmodel.cpp
)

target_include_directories(${component} PRIVATE "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(${component} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")

target_link_libraries(${component}
    PUBLIC FuMathematics
)