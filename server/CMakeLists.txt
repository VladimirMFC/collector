project(cld)
cmake_minimum_required(VERSION 3.1)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(CMAKE_SYSTEM_NAME STREQUAL FreeBSD)
	include_directories("/usr/local/include")
	link_directories("/usr/local/lib")
endif()

find_library(UCL ucl REQUIRED)
find_package(Threads REQUIRED)
find_package(PostgreSQL REQUIRED)

set(TARGET_NAME ${PROJECT_NAME})

aux_source_directory(./src SRC_LIST)
add_executable(${TARGET_NAME} ${SRC_LIST})

target_link_libraries(${TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT} ${UCL} ${PostgreSQL_LIBRARIES})
