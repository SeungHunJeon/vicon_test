cmake_minimum_required(VERSION 3.5)
project(vicon_example)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Set the path for the Vicon SDK
set(VICON_SDK ViconDataStreamSDK_1.11.0.128037h__Linux64)
set(VICON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/${VICON_SDK})

# List of Vicon libraries
set(VICON_LIBRARIES
        ${VICON_DIR}/libViconDataStreamSDK_CPP.so
        ${VICON_DIR}/libboost_chrono.so.1.68.0
        ${VICON_DIR}/libboost_system.so.1.68.0
        ${VICON_DIR}/libboost_thread.so.1.68.0
        ${VICON_DIR}/libboost_timer.so.1.68.0
        )

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${VICON_DIR})

# Create the executable
add_executable(${PROJECT_NAME} src/main.cpp src/vicon.cpp)

# Link the libraries
target_link_libraries(${PROJECT_NAME} ${VICON_LIBRARIES})