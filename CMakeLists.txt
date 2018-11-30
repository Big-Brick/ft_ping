cmake_minimum_required(VERSION 3.9)
FUNCTION(PREPEND var prefix)
   SET(listVar "")
   FOREACH(f ${ARGN})
      LIST(APPEND listVar "${prefix}/${f}")
   ENDFOREACH(f)
   SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(INC Includes)

set(COMMON_INC common)
set(COMMON_SDIR common)

set(NAME1 ft_ping)
project(${NAME1} C)

set(LIBFT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libs/libft)
set(LIBFT_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Libs/libft/CMakeFiles)

set(SDIR Srcs)

set(SOURCES1
		"get_host_addr.c"
		"create_socket.c"
		"fill_ping_pckt.c"
		"stats.c"
		"sigint_handler.c"
		"calculate_ping.c"
		"timeval_math.c"
		"read_msg_data.c"
		"main.c")
PREPEND(SOURCES_REL1 ${SDIR} ${SOURCES1})

set(CMAKE_C_FLAGS "-Wall -Werror -Wextra")

message("EXECUTABLE_OUTPUT_PATH - ${EXECUTABLE_OUTPUT_PATH}")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "Executable output dir" FORCE)
message("EXECUTABLE_OUTPUT_PATH - ${EXECUTABLE_OUTPUT_PATH}")

add_executable(${NAME1} ${SOURCES_REL1})
target_include_directories(${NAME1} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/${INC}/)

add_subdirectory(${LIBFT_SOURCE_DIR} ${LIBFT_BINARY_DIR})

target_link_libraries(${NAME1} libft.a)
include_directories(${LIBFT_INC})

target_link_libraries(${NAME1} "-lm")
