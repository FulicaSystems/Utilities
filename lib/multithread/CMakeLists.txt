set(component multithread)

add_library(${component} STATIC "")

set_property(TARGET ${component}
    PROPERTY PUBLIC_HEADER
    global_threadpool.hpp
    spinlock.hpp
    task.hpp
    threadpool.hpp
)

target_sources(${component}
    PRIVATE
    global_threadpool.hpp
    spinlock.hpp
    spinlock.cpp
    task.hpp
    task.cpp
    threadpool.hpp
    threadpool.cpp
)

target_include_directories(${component} PRIVATE "${CMAKE_CURRENT_LIST_DIR}")
target_include_directories(${component} PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")
