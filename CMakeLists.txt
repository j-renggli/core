PROJECT(core)

cmake_minimum_required(VERSION 2.8)

######## SETUP ########

SET(CMAKE_VERBOSE_MAKEFILE 0)
SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -O -ansi -pedantic -g -pg -Wno-long-long -DDEBUG")
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -O3 -ansi -pedantic -g -pg  -Wno-long-long")

SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../bin)

FIND_PACKAGE(ICU 4.4 REQUIRED)
FIND_PACKAGE(Boost REQUIRED COMPONENTS filesystem system thread)

######## SOURCE CODE ########

INCLUDE_DIRECTORIES(.)

SET(CORE_SRC
src/iobuffer.cpp
src/resultcode.cpp
src/string.cpp

src/buffers/filebuffer.cpp
src/buffers/membuffer.cpp
src/buffers/tempfilebuffer.cpp
src/buffers/volatilebuffer.cpp

src/log/coutdisplay.cpp
src/log/logmanager.cpp

src/random/lincong.cpp
src/random/random.cpp
)

######## LINKER ########

LINK_LIBRARIES(
boost_filesystem
boost_system
boost_thread
icuio
icuuc
)

######## LIBRARIES ########

ADD_LIBRARY(core SHARED ${CORE_SRC})
