# Distributed under the BSD License (See accompanying file /LICENSE )
# CMake build : exorcism tool
cmake_minimum_required(VERSION 3.0)
project(exorcism CXX)
set(TOOL_NAME "exorcism")

# Place targets into their own solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Support C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 14)

# Default build type: Release
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Files
include_directories(${CMAKE_SOURCE_DIR}/source)
set(EXORCISM_SRC_FILES
	${CMAKE_SOURCE_DIR}/source/cube32.cpp
	${CMAKE_SOURCE_DIR}/source/exorcism.cpp
	${CMAKE_SOURCE_DIR}/source/io/read_pla.cpp
	${CMAKE_SOURCE_DIR}/source/io/write_pla.cpp
)

#set target executable
add_library(libexorcism STATIC ${EXORCISM_SRC_FILES})
add_executable(${TOOL_NAME} ${CMAKE_SOURCE_DIR}/source/main.cpp)
target_link_libraries(${TOOL_NAME} libexorcism)

