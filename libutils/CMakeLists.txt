project(utils)
cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(CMAKE_SYSTEM_NAME STREQUAL FreeBSD)
	include_directories("/usr/local/include")
	link_directories("/usr/local/lib")
endif()

find_library(UCL ucl REQUIRED)
find_package(Threads REQUIRED)

set(TARGET_NAME ${PROJECT_NAME})

aux_source_directory(./src SRC_LIST)
add_library(${TARGET_NAME} STATIC ${SRC_LIST})

target_link_libraries(${TARGET_NAME} ${UCL} ${CMAKE_THREAD_LIBS_INIT})
