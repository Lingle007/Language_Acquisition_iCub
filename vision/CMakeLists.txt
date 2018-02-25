cmake_minimum_required(VERSION 3.0)

include_directories(${CMAKE_SOURCE_DIR})

find_package(YARP REQUIRED)

find_package(ICUB)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIR}
		    ${ICUB_INCLUDE_DIR}
                    ${YARP_INCLUDE_DIR})

add_executable(save_img save_image.cpp)
target_link_libraries(save_img ${YARP_LIBRARIES}
			       ${OpenCV_LIBRARIES})
INSTALL(TARGETS save_img DESTINATION bin)
