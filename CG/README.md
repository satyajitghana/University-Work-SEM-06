## Instructions for usage of OpenGL in WSL 

Install ``VcXsrv`` on windows and start it with default settings

Run the following commands to setup the display on WSL \
``export DISPLAY=localhost:0`` \
``sudo service dbus start`` \
``echo $DISPLAY``

## Setup CMake for OpenGL Project

Install the following packages

```
sudo apt update
sudo apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

CMakeLists.txt

```
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS})

target_link_libraries(HelloWorld ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
```