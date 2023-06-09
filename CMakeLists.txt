cmake_minimum_required(VERSION 3.4.1)
project(aspect) #project name

include(cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON) #在构建中获得更多信息
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")
#set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O3 -g -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")
#set(CMAKE_CXX_STANDARD 11)
#aux_source_directory(${PROJECT_SOURCE_DIR}/aspect SRC)指定源文件路径，使用file命令也可以
#include_directories指定头文件目录  ${PROJECT_CURRENT_DIR}
include_directories(.)
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

find_library(YAMLCPP yaml-cpp)
message("***",${YAMLCPP})

set(LIB_SRC
    aspect/log.cc
    aspect/util.cc
    aspect/config.cc
    aspect/thread.cc
)

add_library(aspect SHARED ${LIB_SRC}) #unique lib name `aspect`
force_redefine_file_macro_for_sources(aspect) # 对__FILE__宏重定义输出相对路径 
#add_library(aspect_static STATIC ${LIB_SRC})
#SET_TARGET_PROPERTIES (aspect_static PROPERTIES OUTPUT_NAME "aspect")

add_executable(tests tests/test.cc) #test是内置关键字
add_dependencies(tests aspect)
force_redefine_file_macro_for_sources(tests) # __FILE__
target_link_libraries(tests aspect ${YAMLCPP})

add_executable(test_config tests/test_config.cc) #test是内置关键字
add_dependencies(test_config aspect)
force_redefine_file_macro_for_sources(test_config) # __FILE__
target_link_libraries(test_config aspect ${YAMLCPP})

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
