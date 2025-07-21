cmake_minimum_required(VERSION 3.15...4.0)

project(
	cqp-unit-tests
	VERSION 0.1
	LANGUAGES C
)

add_executable(
	cqp-unit-tests
	src/main.c
)

find_library(LIBSUP cqp)

target_link_libraries(cqp-unit-tests ${LIBSUP})

install(TARGETS cqp-unit-tests)
include(CPack)

