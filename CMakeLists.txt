
cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)

project(touched)

set(CMAKE_VERBOSE_MAKEFILE FALSE)
set(CMAKE_COLOR_MAKEFILE TRUE)

SET (MAINFOLDER ${PROJECT_SOURCE_DIR})
SET (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")

# build type {Debug|Release}
set(CMAKE_BUILD_TYPE Debug)

# find OpenCV
find_package(OpenCV REQUIRED)
# find cvBlob
find_package(cvBlob REQUIRED)

# sources
file(GLOB SRCS
    src/*.c
    src/*.cpp
    src/TUIO/*.cpp
    src/osc/*.cpp
    src/ip/*.cpp
    src/ip/posix/*.cpp
)
message("DEBUG: " ${SRCS})
# headers (let them show up in the IDEs)
file(GLOB HDRS
    src/*.h
    src/*.hpp
)

# 3rd party headers
include_directories(
    ${OpenCV_DIR}
    ${cvBlob_DIR}
)
# 3rd party libraries
set(
  LIBS ${OpenCV_LIBS}
  ${cvBlob_LIBS}

)

message("LIBS:" ${LIBS})

set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${SRCS} ${HDRS})
target_link_libraries(${EXECUTABLE_NAME} ${LIBS})