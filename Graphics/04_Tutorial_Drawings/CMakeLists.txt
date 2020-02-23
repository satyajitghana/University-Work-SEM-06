cmake_minimum_required(VERSION 3.0.0)
project(drawing VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(drawing main.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(drawing ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
