cmake_minimum_required(VERSION 2.8.7)
project(lsd_slam)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS thread filesystem system REQUIRED)
# find_package(Eigen3 REQUIRED)
find_package(Pangolin 0.1 REQUIRED)
find_package(SuiteParse REQUIRED) # Apparently needed by g2o

# FabMap
# uncomment this part to enable fabmap
#add_subdirectory(${PROJECT_SOURCE_DIR}/thirdparty/openFabMap)
#include_directories(${PROJECT_SOURCE_DIR}/thirdparty/openFabMap/include)
#add_definitions("-DHAVE_FABMAP")
#set(FABMAP_LIB openFABMAP )

# SSE flags
add_definitions("-DENABLE_SSE")

# Also add some useful compiler flag
set(CMAKE_CXX_FLAGS
   "${CMAKE_CXX_FLAGS} -msse4.1 -msse3 -msse2 -msse -march=native -O3 -std=c++0x -Wno-deprecated-declarations"
) 

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") 

# Set source files
file(GLOB_RECURSE LSD_SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(
  src
  #${EIGEN3_INCLUDE_DIR}
  /home/symao/workspace/eigen-3.2.8
  ${OpenCV_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIR}
  ${Pangolin_INCLUDE_DIRS}
  ${PROJECT_SOURCE_DIR}/thirdparty/Sophus
  ${CSPARSE_INCLUDE_DIR} #Has been set by SuiteParse
  ${CHOLMOD_INCLUDE_DIR} #Has been set by SuiteParse
  /opt/ros/kinetic/include
)

# build shared library.
add_library(lsd_slam_core SHARED ${LSD_SRC})
target_link_libraries(lsd_slam_core ${FABMAP_LIB} ${Boost_LIBRARIES} ${OpenCV_LIBS}
                      /opt/ros/kinetic/lib/libg2o_core.so
                      /opt/ros/kinetic/lib/libg2o_stuff.so
                      csparse cxsparse
                      /opt/ros/kinetic/lib/libg2o_solver_csparse.so
                      /opt/ros/kinetic/lib/libg2o_csparse_extension.so
                      /opt/ros/kinetic/lib/libg2o_types_sim3.so
                      /opt/ros/kinetic/lib/libg2o_types_sba.so)
# build image node
add_executable(demo example/LSD.cpp)
target_link_libraries(demo lsd_slam_core ${Pangolin_LIBRARIES})

