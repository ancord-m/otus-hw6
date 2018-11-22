cmake_minimum_required(VERSION 3.5)

set(ENV{TRAVIS_BUILD_NUMBER} 1)

project(bulkmt VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(INCLUDE_DIR include)

set(TESTS_DIR test)

set(SRC_DIR src)

set(SRC_LIST	${SRC_DIR}
   )

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

#add_executable(bulkmt ${SRC_DIR}/ip_filter.cpp ${SRC_LIST})

#add_executable(ip_filter_tests ${TESTS_DIR}/ip_filter_tests.cpp ${SRC_LIST})

set_target_properties(bulkmt bulkmt_tests PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS -Wpedantic;-Wall;-Wextra
)

target_include_directories(bulkmt PRIVATE ${INCLUDE_DIR})

set_target_properties(bulkmt_tests PROPERTIES
	COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
	INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_include_directories(bulkmt_tests PRIVATE ${INCLUDE_DIR})

target_link_libraries(bulkmt_tests
	${Boost_LIBRARIES}
)

enable_testing()
