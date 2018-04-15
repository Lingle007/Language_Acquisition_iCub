cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_SOURCE_DIR})

find_package(YARP REQUIRED)

find_package(ICUB)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR}
		    ${ICUB_INCLUDE_DIR}
                    ${YARP_INCLUDE_DIR})

add_executable(iCub_pred iCub_pred.cpp)
target_link_libraries(iCub_pred ${YARP_LIBRARIES}
			       ${OpenCV_LIBRARIES})
INSTALL(TARGETS iCub_pred DESTINATION bin)
