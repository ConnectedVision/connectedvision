cmake_minimum_required (VERSION 2.8)

project(FindOpenCvHelper)

set(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(OpenCV REQUIRED)

file(WRITE "variables.txt" "{
\t\"includeDirs\": \"${OpenCV_INCLUDE_DIRS}\",
\t\"libDir\": \"${OpenCV_LIB_DIR}\",
\t\"libs\": \"${OpenCV_LIBS}\",
}"
)