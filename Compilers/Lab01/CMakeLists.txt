cmake_minimum_required(VERSION 3.0.0)
project(Lab01 VERSION 0.1.0)

include(CTest)
enable_testing()

# setup FLEX
FIND_PACKAGE(FLEX)

FLEX_TARGET(Scanner tokens.l ${CMAKE_CURRENT_BINARY_DIR}/tokens.cpp)

add_executable(Lab01 main.cpp tokens.l ${FLEX_Scanner_OUTPUTS})
target_include_directories(Lab01 PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
