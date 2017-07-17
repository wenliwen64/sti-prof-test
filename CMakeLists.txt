cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(lwen-test)

# Check whether the compiler supports c++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
	message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

# Add to path in order to pick up the FindXXX.cmake files included in this project

find_package(ROOT)
if(NOT ROOT_FOUND)
    message(FATAL_ERROR "Fatal error: ROOT package not found")
endif()

include_directories(
 	${ROOT_INCLUDE_DIR}
	${EIGEN_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}
)

link_directories( ${ROOT_LIBRARY_DIR} )

add_executable(test-trqsq trqsq-test/main.cxx)
target_link_libraries(test-trqsq rt pthread)
