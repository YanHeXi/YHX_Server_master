cmake_minimum_required(VERSION 3.0)
project(yhx)

# include (cmake/utils.cmake)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")

include_directories(.)
include_directories(/home/yanhexi/Downloads/tool)
link_directories(/home/yanhexi/vscode_project/YHX_Server_master/lib)


# message("***",${YAMLCPP})

set(LIB_SRC 
    yhx/log.cc 
    yhx/util.cc
    )

add_library(yhx SHARED ${LIB_SRC})

# force_redefine_file_macro_for_sources(yhx)
# find_library(YAMLCPP yaml-cpp)
# find_library(PTHREAD pthread)

set(LIBS
    yhx
    # pthread
    # yaml-cpp
    )

add_executable(test tests/test.cc)
add_dependencies(test yhx)
# force_redefine_file_macro_for_sources(test)
target_link_libraries(test ${LIBS})




SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
