cmake_minimum_required(VERSION 3.5)

set(ENV{TRAVIS_BUILD_NUMBER} 1)

project(bulk VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(INCLUDE_DIR include)

set(TESTS_DIR test)

set(TESTS_LIST	${TESTS_DIR}/command_collector_tests.cpp
	)

set(SRC_DIR src)

set(SRC_LIST	${SRC_DIR}/main.cpp
				${SRC_DIR}/command_collector.cpp
				${SRC_DIR}/console_printer.cpp
				${SRC_DIR}/bulk_to_file_writer.cpp
   )

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(bulk ${SRC_LIST})

add_executable(bulk_tests ${TESTS_LIST} ${SRC_DIR}/command_collector.cpp)

set_target_properties(bulk bulk_tests PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS -Wpedantic;-Wall;-Wextra
)

target_include_directories(bulk PRIVATE ${INCLUDE_DIR})

set_target_properties(bulk_tests PROPERTIES
	COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
	INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_include_directories(bulk_tests PRIVATE ${INCLUDE_DIR})

target_link_libraries(bulk_tests
	${Boost_LIBRARIES}
)

enable_testing()
