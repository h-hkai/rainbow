cmake_minimum_required(VERSION 3.0)
project(rainbow)

include (cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")

include_directories(.)
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

set(LIB_SRC
    rainbow/address.cpp
    rainbow/config.cpp
    rainbow/fd_manager.cpp
    rainbow/fiber.cpp
    rainbow/hook.cpp
    rainbow/iomanager.cpp
    rainbow/log.cpp
    rainbow/scheduler.cpp
    rainbow/socket.cpp
    rainbow/timer.cpp
    rainbow/thread.cpp
    rainbow/util.cpp
    )

add_library(rainbow SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(rainbow)
#add_library(rainbow_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (rainbow_static PROPERTIES OUTPUT_NAME "rainbow")

find_library(YAMLCPP yaml-cpp)
find_library(PTHREAD pthread)
#set(LIBS ${LIBS} rainbow)
#set(LIBS ${LIBS} dl)
#set(LIBS ${LIBS} ${YAMLCPP})
#set(LIBS ${LIBS} ${PTHREAD})

set(LIBS
        rainbow
        dl
        pthread
        yaml-cpp)

message("***", ${LIBS})

add_executable(test tests/test.cpp)
add_dependencies(test rainbow)
force_redefine_file_macro_for_sources(test) #__FILE__
target_link_libraries(test ${LIBS})

add_executable(test_hook tests/test_hook.cpp)
add_dependencies(test_hook rainbow)
force_redefine_file_macro_for_sources(test_hook) #__FILE__
target_link_libraries(test_hook ${LIBS})

add_executable(test_address tests/test_address.cpp)
add_dependencies(test_address rainbow)
force_redefine_file_macro_for_sources(test_address) #__FILE__
target_link_libraries(test_address ${LIBS})

add_executable(test_socket tests/test_socket.cpp)
add_dependencies(test_socket rainbow)
force_redefine_file_macro_for_sources(test_socket) #__FILE__
target_link_libraries(test_socket ${LIBS})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
